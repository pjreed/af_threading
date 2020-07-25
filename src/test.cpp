#include <arrayfire.h>
#include <iostream>
#include <thread>

/*
 * Functor for computing homography.
 * The concept is that we have a set of pre-computed features, and we want
 * to iterate through other images, compute their features, and match them
 * to the pre-computed ones.
 */
class SharedFeatureHomographyComputer
{
public:
  void operator()() {
    af::features f1;
    af::array d1;
    af::orb(f1, d1, img1_);
  
    af::array idx, dist;
    af::hammingMatcher(idx, dist, d1, d2_);
  
    af::array nearest = af::where(dist < 80);
    af::array near_x1 = f1.getX()(nearest);
    af::array near_y1 = f1.getY()(nearest);
    af::array near_x2 = f2_.getX()(nearest);
    af::array near_y2 = f2_.getY()(nearest); 
  
    af::array h;
    int inliers;
    af::homography(h, inliers, near_x1, near_y1, near_x2, near_y2);
  }

  af::array img1_;
  af::features f2_;
  af::array d2_;
};

int main(int argc, char** argv)
{
  // Load our saple image
  af::array img1 = af::loadImage("../src/book1.png");
  af::array img2 = af::loadImage("../src/book2.png");
  const int num_iters = 200;

  // Pre-compute features for img2
  af::features f2;
  af::array d2;
  af::orb(f2, d2, img2);

  // Save img1 into the functor; its features will be re-computed every time
  SharedFeatureHomographyComputer sfhc;
  sfhc.img1_ = img1;
  sfhc.d2_ = d2;
  sfhc.f2_ = f2;

  // Run 200 loops on the same thread; this never crashes
  std::cout << "Starting " << num_iters << " sequential iterations." << std::endl;
  for (int i = 0; i < num_iters; i++)
  {
    sfhc();
  }

  // Run 200 loops in threads; this always crashes
  // Note that this seems to be specifically tied to the af::features object;
  // if you modify the functor so it re-computes img2's features every time
  // and we do not assign them to a class member, this does not crash.
  std::cout << "Starting " << num_iters << " threads." << std::endl;
  std::vector<std::thread> threads;
  for (int i = 0; i < num_iters; i++)
  {
    threads.emplace_back(sfhc);
  }
  for (auto& t : threads)
  {
    t.join();
  }
  std::cout << "Finished." << std::endl;

  return 0;
}

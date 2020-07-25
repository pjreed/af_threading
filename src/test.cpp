#include <arrayfire.h>

int main(int argc, char** argv)
{
  af::setBackend(AF_BACKEND_CUDA);
  return 0;
}

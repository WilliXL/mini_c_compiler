#include "parse.hpp"

using namespace std;

namespace generator
{

class Generator
{
    public:
        Generator(parser::Program* p) { root = p; };
        void generate(string name);
    private:
        parser::Program* root;
};

} // namespace generator
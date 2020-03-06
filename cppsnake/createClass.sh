pushd src/ >/dev/null
vim -c ':normal dG' -c ':Stdheader' -c ':normal dd' -c ':x' $1.hpp
echo -e "#ifndef $(echo $1 | tr a-z A-Z)_HPP
#define $(echo $1 | tr a-z A-Z)_HPP\n
#include <iostream>\n
class $1 {
public:
private:
};\n
#endif" >> $1.hpp
popd >/dev/null

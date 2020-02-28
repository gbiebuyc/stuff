vim -c ':normal dG' -c ':Stdheader' -c ':normal dd' -c ':x' $1.hpp
echo -e "#ifndef $(echo $1 | tr a-z A-Z)_HPP
# define $(echo $1 | tr a-z A-Z)_HPP\n
#include <iostream>\n
class $1 {
private:\n
public:
    $1(void);
    $1($1 const & src);
    ~$1(void);
    $1 &operator=($1 const &rhs);
};\n
std::ostream &operator<<(std::ostream &o, $1 const &rhs);\n
#endif" >> $1.hpp

vim -c ':normal dG' -c ':Stdheader' -c ':normal dd' -c ':x' $1.cpp
echo -e "#include \"$1.hpp\"\n
$1::$1(void) {
}\n
$1::$1($1 const &src) {
    *this = src;
}\n
$1::~$1(void) {
}\n
$1 &$1::operator=($1 const &rhs) {
    // _foo = rhs.getFoo();
    return *this;
}\n
std::ostream &operator<<(std::ostream &o, $1 const &rhs) {
    //o << \"The value of _foo is: \" << rhs.getFoo();
    return o;
}" >> $1.cpp

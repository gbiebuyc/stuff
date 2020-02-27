vim -c ':normal dG' -c ':Stdheader' -c ':normal dd' -c ':x' $1.hpp
echo -e "#ifndef $(echo $1 | tr a-z A-Z)_HPP" >> $1.hpp
echo -e "# define $(echo $1 | tr a-z A-Z)_HPP\n" >> $1.hpp
echo -e "#include <iostream>\n" >> $1.hpp
echo -e "class $1" >> $1.hpp
echo -e "{" >> $1.hpp
echo -e "private:" >> $1.hpp
echo -e "" >> $1.hpp
echo -e "public:" >> $1.hpp
echo -e "    $1();" >> $1.hpp
echo -e "    ~$1();" >> $1.hpp
echo -e "};\n" >> $1.hpp
echo -e "#endif" >> $1.hpp

vim -c ':normal dG' -c ':Stdheader' -c ':normal dd' -c ':x' $1.cpp
echo -e "#include \"$1.hpp\"\n" >> $1.cpp
echo -e "$1::$1(void) {" >> $1.cpp
echo -e "}" >> $1.cpp
echo -e "" >> $1.cpp
echo -e "$1::~$1(void) {" >> $1.cpp
echo -e "}" >> $1.cpp

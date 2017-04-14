#Make build directory
if [ ! -d build/config ]; then
	mkdir build/config
else
	rm build/config/* -f
fi

#Create hex for each file
for filename in etc/*; do
	xxd -i $filename > build/config/$(echo $filename | sed "s/etc\///g" )
done

#Begin config.cpp
echo -e "#include \"../include/config.h\"\n" 			>  src/config.cpp
echo -e "config::config()\n{"  					>> src/config.cpp
echo -e "\tthis->defaults = new std::vector<cfile>;" 		>> src/config.cpp
echo -e "\tunsigned char *temp;" 				>> src/config.cpp

#Add all hex into config.cpp
for filename in build/config/*; do
	#Find variables from hex file
	SIZE=$(grep -oP "(?<= )[0-9].*(?=;)" $filename | tr -d '\n')
	NAME=$(grep -Po "(?<= etc_).*_.*(?=\[\])" $filename | sed "s/_/./g" | tr -d '\n')
	DATA=$(awk "/{/,/}/{print}" $filename | sed "s/;//g" | sed "s/unsigned char.*= //g" | tr -d '\n' | sed "s/  / /g" )

	echo -e "\n\ttemp = new unsigned char[$SIZE] $DATA;"				>> src/config.cpp
	echo -e "\tthis->defaults->emplace_back( \"$NAME\", $SIZE, temp );"	>> src/config.cpp
	echo -e "\tdelete[] temp;"						>> src/config.cpp
done
echo -e "}\n\nconfig::~config()\n{\n\tdefaults->clear();\n\tdelete defaults;\n}" 			>> src/config.cpp

#Make build directory
if [ ! -d build/config ]; then
	mkdir build/config
fi

#Create hex for each file
for filename in etc/*; do
	xxd -i $filename > build/config/$(echo $filename | sed "s/etc\///g" )
done

#Begin config.cpp
echo -e "#include \"../include/config.h\"\n" > src/config.cpp
echo -e "configfiles config;\n" >> src/config.cpp
#Add all hex into config.cpp
for filename in build/config/*; do
	echo -ne "config.add( \"" 									>> src/config.cpp
	grep -Po "(?<= etc_).*_.*(?=\[\])" $filename | sed "s/_/./g" | tr -d '\n'	>> src/config.cpp
	echo -ne "\", \t" >> src/config.cpp
	grep -oP "(?<= )[0-9].*(?=;)" $filename | tr -d '\n'					>> src/config.cpp
	echo -ne ", \t" >> src/config.cpp
	awk "/{/,/}/{print}" $filename | sed "s/;//g" | sed "s/unsigned char.*= //g" | tr -d '\n' | sed "s/  / /g" >> src/config.cpp
	echo " );" >> src/config.cpp
done

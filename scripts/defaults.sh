if [ ! -d build/config ]; then
	mkdir build/config
fi

for filename in etc/*; do
	xxd -i $filename > build/config/$(echo $filename | sed "s/etc\///g" | sed "s/.conf/.hex/g" )
done

#include "../include/findfiles.h"

std::vector<std::string> findfiles( std::string folder )
{
	std::vector<DIR*> dirs;
        std::vector<std::string> curdir;
        std::vector<std::string> files;

        //Get pointer to directory for config files
        curdir.push_back(folder);
        dirs.push_back( opendir( curdir[0].c_str() ) );

        //For each directory
        //Using int so can change size from within
        for( unsigned int i=0; i!=dirs.size(); i++)
        {
                //while there are still more entries
                dirent *cur = readdir(dirs[i]);
                while( cur )
                {
                        //ignore hidden files
                        if( !( cur->d_name[0] == '.' ) )
                        {
                                //Get location and append file/folder name
                                std::string loc(curdir[i]);
                                loc += "/";
                                loc += cur->d_name;

                                //If a directory add to list of directories to search
                                if( cur->d_type == DT_DIR )
                                {
                                        dirs.push_back( opendir( loc.c_str() ) );
                                        curdir.push_back( loc.c_str() );
                                }
                                else    files.push_back( loc );
                        }
                        cur = readdir(dirs[i]);
                }
        }
	for( std::vector<DIR*>::iterator it = dirs.begin(); it != dirs.end(); it++ )	closedir(*it);

	return files;
}

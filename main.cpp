#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <iomanip>

int main( int argc, char *argv[] )
{
    if( argc != 4 )
    {
        std::cout << "usage:\n"
            << argv[0] << " inputfilename outputfilename arrayname\n";
        return 1;
    }
    std::ifstream in_file;
    in_file.open(argv[1]);
    if( !in_file.is_open() )
        return 1;
    std::istreambuf_iterator<char> beg(in_file);
    std::istreambuf_iterator<char> end;
    std::vector<unsigned char> content;
    std::copy( beg, end, std::back_inserter( content ) );
    std::ofstream out_file;
    out_file.open( argv[2] );
    if( !out_file.is_open() )
        return 1;
    out_file << "unsigned char const " << argv[3] << "[" << content.size() << "] =\n{";
    for( int i=0; i<content.size(); ++i )
    {
        if( i )
            out_file << ",";
        out_file << ( ( i%16 ) ? " " : "\n\t" );
        out_file << "0x" << std::hex << std::setw( 2 ) << std::setfill( '0' )<< static_cast<unsigned int>( content[i] );
    }
    out_file << "\n};\n";
    return 0;
}

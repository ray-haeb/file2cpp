#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

int main( int argc, char *argv[] ) {
    if( argc < 3 ) {
        std::cout << "usage:" << std::endl
                << argv[0] << " outputfilename inputfilename1 [inputfilename2, ...]" << std::endl;
        return 1;
    }

    std::string out_file_name_cpp = std::string( argv[1] ).append( ".cpp" );
    std::string out_file_name_hpp = std::string( argv[1] ).append( ".hpp" );
    std::ofstream out_file_cpp;
    out_file_cpp.open( out_file_name_cpp );
    if( !out_file_cpp.is_open() )
    {
        std::cerr << "cannot open output file: \"" << out_file_name_cpp << "\"" << std::endl;
        return 1;
    }
    std::ofstream out_file_hpp;
    out_file_hpp.open( out_file_name_hpp );
    if( !out_file_hpp.is_open() )
    {
        std::cerr << "cannot open output file: \"" << out_file_name_hpp << "\"" << std::endl;
        return 1;
    }
    out_file_hpp << "#pragma once" << std::endl;
    out_file_hpp << "#include <array>" << std::endl << std::endl;
    out_file_cpp << "#include <array>" << std::endl << std::endl;
    for( int i = 2; i<argc; ++i )
    {
        std::string input_filename( argv[i] );
        std::string array_name;
        std::transform(
            input_filename.begin(),
            input_filename.end(),
            std::back_inserter( array_name ),
            []( char in  ) -> char { return ( std::isalnum( in ) || in == '_' )? in : '_'; }
        );
        std::ifstream in_file;
        in_file.open( input_filename );
        if( !in_file.is_open() )
        {
            std::cerr << "cannot open input file: \"" << input_filename << "\"" << std::endl;
            continue;
        }
        std::vector<char> content;
        std::copy(
                std::istreambuf_iterator<char>(in_file),
                std::istreambuf_iterator<char>(),
                std::back_inserter(content)
        );
        content.push_back(0);
        out_file_hpp << "extern std::array<char const," << content.size() << "> " << array_name << ";" << std::endl;
        out_file_cpp << "std::array<char const," << content.size() << "> " << array_name << " ="  << std::endl << "{";
        for( int j=0; j<content.size(); ++j )
        {
            if( j )
                out_file_cpp << ",";
            if( !( j%16 ) )
                out_file_cpp << std::endl << "\t";
            out_file_cpp << std::setw( 5 ) << std::setfill( ' ' ) << static_cast<int>( content[j] );
        }
        out_file_cpp << std::endl << "};" << std::endl << std::endl;
    }
    return 0;
}

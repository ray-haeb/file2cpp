#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <iomanip>

int main( int argc, char *argv[] ) {
    if (argc != 4) {
        std::cout << "usage:\n"
                << argv[0] << " inputfilename outputfilename arrayname\n";
        return 1;
    }
    std::vector<char> content;
    {
        std::ifstream in_file;
        in_file.open(argv[1]);
        if (!in_file.is_open()) {
            std::cerr << "cannot open input file: \"" << argv[1] << "\"\n";
            return 1;
        }
        std::copy(
                std::istreambuf_iterator<char>(in_file),
                std::istreambuf_iterator<char>(),
                std::back_inserter(content)
        );
        content.push_back(0);
    }
    std::string out_file_name_cpp = std::string( argv[2] ).append( ".cpp" );
    std::string out_file_name_hpp = std::string( argv[2] ).append( ".hpp" );
    std::ofstream out_file_cpp;
    out_file_cpp.open( out_file_name_cpp );
    if( !out_file_cpp.is_open() )
    {
        std::cerr << "cannot open output file: \"" << out_file_name_cpp << "\"\n";
        return 1;
    }
    std::ofstream out_file_hpp;
    out_file_hpp.open( out_file_name_hpp );
    if( !out_file_hpp.is_open() )
    {
        std::cerr << "cannot open output file: \"" << out_file_name_hpp << "\"\n";
        return 1;
    }
    out_file_hpp << "#include <array>\n\n";
    out_file_cpp << "#include <array>\n\n";
    out_file_hpp << "extern std::array<char const," << content.size() << "> " << argv[3] << " const;\n";
    out_file_cpp << "std::array<char const," << content.size() << "> " << argv[3] << " const =\n{";
    for( int i=0; i<content.size(); ++i )
    {
        if( i )
            out_file_cpp << ",";
        out_file_cpp << ( ( i%16 ) ? " " : "\n\t" );
        out_file_cpp << std::setw( 4 ) << std::setfill( ' ' ) << static_cast<int>( content[i] );
    }
    out_file_cpp << "\n};\n";
    return 0;
}

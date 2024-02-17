#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
std::string bitmask;
std::string binary_mask;

void convert_binary(const std::string& bitmask) {
    binary_mask = "";

    for (char c : bitmask) {
        switch (c) {
            case '0':
                binary_mask += "0000";
                break;
            case '1':
                binary_mask += "0001";
                break;
            case '2':
                binary_mask += "0010";
                break;
            case '3':
                binary_mask += "0011";
                break;
            case '4':
                binary_mask += "0100";
                break;
            case '5':
                binary_mask += "0101";
                break;
            case '6':
                binary_mask += "0110";
                break;
            case '7':
                binary_mask += "0111";
                break;
            case '8':
                binary_mask += "1000";
                break;
            case '9':
                binary_mask += "1001";
                break;
            case 'A':
                binary_mask += "1010";
                break;
            case 'B':
                binary_mask += "1011";
                break;
            case 'C':
                binary_mask += "1100";
                break;
            case 'D':
                binary_mask += "1101";
                break;
            case 'E':
                binary_mask += "1110";
                break;
            case 'F':
                binary_mask += "1111";
                break;
        }
    }
}

int main() {
    std::cout << "printing the relocating address!!\n\n";
    int start;
    std::string str = "";
    int address;
    int opcode;
    int final_addr;
    int text_rec_len;
    std::string rec_addr;
    std::string length;
    std::string col_one;
    std::string obj_addr;
    std::string prog_name;

    std::ifstream fp("RLIN.txt");

    std::cout << "Enter starting address : ";
    std::cin >> std::hex >> start;

    fp >> col_one;

    std::cout << "\nLocation\tObject Code";

    while (col_one != "E")
        {
            if (col_one == "H")
        {
            fp >> prog_name >> std::hex >> rec_addr >> length >> col_one;
        }

        if (col_one == "T") {
            fp >> std::hex >> address >> text_rec_len >> bitmask;



            address += start;

            convert_binary(bitmask);

            for (int i = 0; i < 10; i++)
            {
                fp >> std::hex >> opcode >> obj_addr;

                if (binary_mask[i] == '0')
                    final_addr = std::stoi(obj_addr, nullptr, 16);

                else
                    final_addr = std::stoi(obj_addr, nullptr, 16) + start;

                //str+= to_string(opcode)+to_string(final_addr)+" ";
               // cout<<"final addr:"<<final_addr<<endl;
                //str += std::to_string(final_addr) + " ";
                std::cout << "\n" << std::hex << address << "\t\t" << std::hex << opcode << std::hex << final_addr;
                std::stringstream ss;
                ss << std::hex << opcode << std::hex << final_addr;
                str += ss.str() + " ";
                address += 3;

                if (obj_addr.back() == '$')
                    break;
            }
           // std::cout << "\nXXXX             XXXXXX";

            fp >> col_one;
        }
    }
        cout<<endl;
        //std::cout << str << " ";

    fp.close();

    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    //cout<<"try"<<endl;
     std::cout << "\nLocation\tObject Code"<<endl;


    size_t numRows = 3; // For example, 5 rows
    size_t cols = 3;    // 4 columns
    int num=1000;
    for (size_t i = 0; i < numRows; ++i)
    {
        std::cout << std::hex << start + i * 0x10 << "\t"; // First column in decimal
        for (size_t j = 0; j < cols; ++j)
        {
            std::cout << str.substr((i * cols + j) * 8, 8) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl; //
    return 0;
}

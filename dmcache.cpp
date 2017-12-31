#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class CacheLine{
    public:
        int tag;
        int dirty;
        int data[8];
        
        CacheLine() {
            tag = 0;
            dirty = 0;
            for(int i=0; i<8; i++){
                data[i] = 0;
            }
        }
};

void print(CacheLine (&cache)[32], int line, int offset, int hit, int dirty, ofstream& out)
{
    out << hex << uppercase << setfill('0') << setw(2) << cache[line].data[offset] << " " << hit << " " << dirty << endl;
}

    void write(CacheLine (&cache)[32], int (&memory)[65535], int tag, int line, int offset, int data){
            int hit;

            if(cache[line].tag == tag){
               cache[line].data[offset] = data;
               cache[line].dirty = 1;
               hit = 1;
            }
            
            else{
                hit = 0;
                if(cache[line].dirty == 1){
                    for(int i = 0; i < 8; i++)
                    {
                        memory[cache[line].tag * 8 + i] = cache[line].data[i];
                    }
                }
                
                
                for(int i = 0; i < 8; i++)
                    {
                        cache[line].data[i] = memory[tag * 8 + i];
                    }
                cache[line].tag = tag;
                cache[line].data[offset] = data;
                cache[line].dirty = 1;
            }
}

void read(CacheLine (&cache)[32], int (&memory)[65535], int tag, int line, int offset, int data, ofstream& out){
    int dirty = cache[line].dirty;
    int hit;
    if(cache[line].tag == tag)
    {
        hit = 1;
    }
            
    else{
        hit = 0;
        if(cache[line].dirty == 1){
            for(int i = 0; i < 8; i++)
            {
                memory[cache[line].tag * 8 + i] = cache[line].data[i];
            }
        }
                
        for(int i = 0; i < 8; i++)
        {
            cache[line].data[i] = memory[tag * 8 + i];
        }
        
        cache[line].tag = tag;
        cache[line].dirty = 0;
        
    }
    
    print(cache, line, offset, hit, dirty, out);
}

int main(int argc, char** argv){

    ifstream infile;
    infile.open(argv[1]);
    
    ofstream out;
    out.open("dm-out.txt");
    
    CacheLine cache[32];
    int memory[65535];
    int tag, line, offset, address, opcode, data, hit = 0;
    
    while(infile >> hex >> address >> opcode >> data){
        tag = (address >> 5);
        offset = address & 7;
        line = (address / 8) % 32;
        
        if(opcode == 0xFF){
            write(cache, memory, tag, line, offset, data);
            
        }
        
        else{
            read(cache, memory, tag, line, offset, data, out);
        }
    }
    infile.close();
   out.close();

    return 0;
}

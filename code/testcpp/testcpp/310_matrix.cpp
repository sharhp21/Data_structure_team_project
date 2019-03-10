//
//  310_matrix.cpp
//  testcpp
//
//  Created by Hyeontae on 04/12/2018.
//  Copyright © 2018 onemoon. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include "string"

using namespace std;

string* myStringSplit(string strTarget, string strTok);

double cal_edge(double f_x,double f_y,double s_x,double s_y){
    double sub_result = pow((f_x-s_x),2.0) + pow((f_y-s_y),2.0);
    return sqrt(sub_result);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//int main(int argc, const char * argv[]) {
int main() {
    cout <<"hello \n";
    double pos1[9][2];
    double pos2[9][2];
    double pos3[24][2];
    double pos4[24][2];
    double pos5[24][2];
    
    
    double f1[9][9] = {0,};
    double f2[9][9]= {0,};
    double f3[24][24]= {0,};
    double f4[24][24]= {0,};
    double f5[24][24]= {0,};
    
//    f1[1][2] = 27;
//    f1[1][6] = 20;
//    f1[2][3] = 6;
//    f1[2][4] = 11;
//    f1[3][4] = 6;
//    f1[3][7] = 16;
//    f1[4][7] = 17;
//    f1[5][6] = 13;
//    f1[5][8] = 47;
//    f1[6][7] = 32;
//    f1[6][8] = 34;
    
    
    string filePath = "mytext.txt";
    
    bool second_flag = false;
    

    
    ifstream openFile(filePath.data());
    if( openFile.is_open() ){
        string line;
        getline(openFile, line);
        string* splitedLine = myStringSplit(line, "\r");
        
        int line_count = 0;
        while(true) {
            string* splited = myStringSplit(splitedLine[line_count++], "\t");
            
            if(splited[0].length() == 1 && second_flag == true) {
                break;
            } else if ( splited[0].length() == 1 ) {
                second_flag = true;
                continue;
            }
            
            if( !second_flag ) {
                // x y position 저장

                int floor = stoi(splited[0])/100;
                int target = (stoi(splited[0])%100)-1;
                double posx = stod(splited[1]);
                double posy = stod(splited[2]);
                switch (floor) {
                    case 1:
                        pos1[target][0] = posx;
                        pos1[target][1] = posy;
                        break;
                    case 2:
                        pos2[target][0] = posx;
                        pos2[target][1] = posy;
                        break;
                    case 3:
                        pos3[target][0] = posx;
                        pos3[target][1] = posy;
                        break;
                    case 4:
                        pos4[target][0] = posx;
                        pos4[target][1] = posy;
                        break;
                    case 5:
                        pos5[target][0] = posx;
                        pos5[target][1] = posy;
                        break;
                    default:
                        break;
                }
            } else {
                // 두번째 단계 계산해서 거리 넣기
                
                int base_node_number = stoi(splited[0]);
                int base_floor = (base_node_number/100);
                int base_idx = (base_node_number%100)-1;
                
                
                for(int k=1;k<5;k++) {
                    int target = splited[k] != "" ? stoi(splited[k]) : -1;
                    if(target == -1) continue;
                    if(target < base_node_number) continue;
                    
                    int target_idx = (target%100)-1;
                    
                    switch (base_floor) {
                        case 1:
                            f1[base_idx][target_idx] = cal_edge(pos1[base_idx][0], pos1[base_idx][1], pos1[target_idx][0], pos1[target_idx][1]);
                            break;
                        case 2:
                            f2[base_idx][target_idx] = cal_edge(pos2[base_idx][0], pos2[base_idx][1], pos2[target_idx][0], pos2[target_idx][1]);
                            break;
                        case 3:
                            f3[base_idx][target_idx] = cal_edge(pos3[base_idx][0], pos3[base_idx][1], pos3[target_idx][0], pos3[target_idx][1]);
                            break;
                        case 4:
                            f4[base_idx][target_idx] = cal_edge(pos4[base_idx][0], pos4[base_idx][1], pos4[target_idx][0], pos4[target_idx][1]);
                            break;
                        case 5:
                            f5[base_idx][target_idx] = cal_edge(pos5[base_idx][0], pos5[base_idx][1], pos5[target_idx][0], pos5[target_idx][1]);
                            break;
                        default:
                            break;
                    }
                    
                }
                
                
                
            }
            
            

        }
        
        openFile.close();
    }
    
    
    
    // 양 방향으로 만들어 줘야 한다.
    for(int p=0;p <24;p++){
        for(int i=0;i <24;i++){
            cout << f5[p][i] <<" ";
        }
        cout << "\n";
    }
    
    
    
    
}


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


string* myStringSplit(string strTarget, string strTok)
{
    int     nCutPos;
    int     nIndex     = 0;
    string* strResult = new string[200];
    
    while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
    {
        if (nCutPos > 0)
        {
            strResult[nIndex++] = strTarget.substr(0, nCutPos);
        }
        strTarget = strTarget.substr(nCutPos+1);
    }
    
    if(strTarget.length() > 0)
    {
        strResult[nIndex++] = strTarget.substr(0, nCutPos);
    }
    
    return strResult;
}

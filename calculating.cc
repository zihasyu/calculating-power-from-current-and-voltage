#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// 假设数据是整数类型
// void parseData(const std::string &line, std::vector<int> &data)
// {
//     std::stringstream ss(line);
//     int number;
//     while (ss >> number)
//     {
//         data.push_back(number);
//     }
// }
// void parseData(const std::string &line, std::vector<double> &data)
// {
//     std::stringstream ss(line);
//     double number;
//     while (ss >> number)
//     {
//         data.push_back(number);
//     }
// }
int running(const std::string filePath);
void parseData(const std::string &text, std::vector<double> &data)
{
    std::istringstream iss(text);
    std::string temp;
    while (iss >> temp)
    {
        try
        {
            // 尝试将字符串转换为double并添加到vector中
            data.push_back(std::stod(temp));
        }
        catch (const std::invalid_argument &e)
        {
            // 如果转换失败（例如，字符串不是一个数字），则忽略该字符串
            continue;
        }
    }
}

int main(int argc, char *argv[])
{
    // 检查是否有命令行参数传入
    if (argc < 2)
    {
        std::cerr << "使用方法: " << argv[0] << " <文件路径>" << std::endl;
        return 1;
    }
    // 第一个命令行参数是文件路径
    std::string filePath = argv[1];
    running(filePath);
    return 0;
}

int running(const std::string filePath)
{
    std::ifstream file(filePath); // 替换为你的文件名
    std::string line;
    std::vector<double> data1, data2, data3, data4, data5;
    int count = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            // 查找特定行
            if (line.find("set datasetList($curveName) {") != std::string::npos)
            {
                // 读取下一行，即第一个大括号开始的行
                // if (getline(file, line) && line.find("{") != std::string::npos)
                // {
                // 读取并解析两组数据
                for (int i = 0; i < 2; ++i)
                {
                    if (getline(file, line) && line.find("{") != std::string::npos)
                    {
                        // std::cout << line << std::endl;
                        if (count == 0)
                        {
                            // std::cout << line << std::endl;
                            parseData(line, data1);
                            getline(file, line);
                            // std::cout << line << std::endl;
                            parseData(line, data2);
                        }

                        else if (count == 1)
                        {
                            // std::cout << line << std::endl;
                            parseData(line, data3);
                            getline(file, line);
                            // std::cout << line << std::endl;
                            parseData(line, data4);
                        }
                        count++;
                        // 跳过闭合的大括号
                    }
                }
                // 跳过外层大括号的闭合
                getline(file, line);
                // }
                if (count >= 2)
                    break; // 只需要前两组数据
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file";
        return 1;
    }

    // 输出结果，用于验证
    // for (double num : data1)
    //     std::cout << num << " ";
    // std::cout << "\n";
    // for (double num : data2)
    //     std::cout << num << " ";
    // std::cout << "\n";
    // for (double num : data3)
    //     std::cout << num << " ";
    // std::cout << "\n";
    // for (double num : data4)
    //     std::cout << num << " ";
    // std::cout << "\n";
    for (size_t i = 0; i < data2.size(); ++i)
    {
        // 对应位置相乘并添加到data5
        data5.push_back(data2[i] * data4[i]);
    }
    // for (double num : data5)
    //     std::cout << num << " ";
    // std::cout << "\n";
    std::ofstream outFile("output.txt");
    if (outFile.is_open())
    {
        for (size_t i = 0; i < data1.size() && i < data5.size(); ++i)
        {
            outFile << data1[i] << " " << data5[i] << "\n";
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing.";
    }
    return 0;
}

// int main()
// {
//     std::ifstream file("1.5"); // 替换为你的文件名
//     std::string line;
//     std::vector<double> data1, data2, data3, data4, data5;
//     int count = 0;

//     if (file.is_open())
//     {
//         while (getline(file, line))
//         {
//             // 查找特定行
//             if (line.find("set datasetList($curveName) {") != std::string::npos)
//             {
//                 // 读取下一行，即第一个大括号开始的行
//                 // if (getline(file, line) && line.find("{") != std::string::npos)
//                 // {
//                 // 读取并解析两组数据
//                 for (int i = 0; i < 2; ++i)
//                 {
//                     if (getline(file, line) && line.find("{") != std::string::npos)
//                     {
//                         // std::cout << line << std::endl;
//                         if (count == 0)
//                         {
//                             // std::cout << line << std::endl;
//                             parseData(line, data1);
//                             getline(file, line);
//                             // std::cout << line << std::endl;
//                             parseData(line, data2);
//                         }

//                         else if (count == 1)
//                         {
//                             // std::cout << line << std::endl;
//                             parseData(line, data3);
//                             getline(file, line);
//                             // std::cout << line << std::endl;
//                             parseData(line, data4);
//                         }
//                         count++;
//                         // 跳过闭合的大括号
//                     }
//                 }
//                 // 跳过外层大括号的闭合
//                 getline(file, line);
//                 // }
//                 if (count >= 2)
//                     break; // 只需要前两组数据
//             }
//         }
//         file.close();
//     }
//     else
//     {
//         std::cerr << "Unable to open file";
//         return 1;
//     }

//     // 输出结果，用于验证
//     // for (double num : data1)
//     //     std::cout << num << " ";
//     // std::cout << "\n";
//     // for (double num : data2)
//     //     std::cout << num << " ";
//     // std::cout << "\n";
//     // for (double num : data3)
//     //     std::cout << num << " ";
//     // std::cout << "\n";
//     // for (double num : data4)
//     //     std::cout << num << " ";
//     // std::cout << "\n";
//     for (size_t i = 0; i < data2.size(); ++i)
//     {
//         // 对应位置相乘并添加到data5
//         data5.push_back(data2[i] * data4[i]);
//     }
//     for (double num : data5)
//         std::cout << num << " ";
//     std::cout << "\n";
//     std::ofstream outFile("output.txt");
//     if (outFile.is_open())
//     {
//         for (size_t i = 0; i < data1.size() && i < data5.size(); ++i)
//         {
//             outFile << data1[i] << " " << data5[i] << "\n";
//         }
//         outFile.close();
//     }
//     else
//     {
//         std::cerr << "Unable to open file for writing.";
//     }
//     return 0;
// }
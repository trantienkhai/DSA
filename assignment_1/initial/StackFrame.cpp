#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;
// Hàm này tách chuỗi đọc vào thành mảng chuỗi
char **split_string(const string &input_string, int &num_words)
{
    // Đếm số lượng từ tách được
    num_words = 0;
    string str = input_string + " "; // Đảm bảo có dấu cách ở cuối chuỗi để xử lý từ cuối cùng
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == ' ')
        {
            ++num_words;
        }
    }

    // Cấp phát mảng con trỏ
    char **words = new char *[num_words];

    // Tách từ và sao chép vào mảng
    int start = 0;
    int index = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == ' ')
        {
            int length = i - start;
            if (length > 0)
            {
                words[index] = new char[length + 1];
                str.copy(words[index], length, start);
                words[index][length] = '\0';
                ++index;
            }
            start = i + 1;
        }
    }

    return words;
}

// Hàm giải phóng bộ nhớ của mảng các từ
void free_string(char **words, int num_words)
{
    for (int i = 0; i < num_words; ++i)
    {
        delete[] words[i]; // Giải phóng từng từ
    }
    delete[] words; // Giải phóng mảng con trỏ
}

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE) {}

void StackFrame::run(string filename)
{
    Array array;
    Stack stack;
    float top_val = 0;   // du lieu tren cung stack
    float below_val = 0; // du lieu ben duoi stack
    char **result;       // con tro den mang sau khi tach
    int num_words = 0;   // so tu trong moi dong lenh
    int line = 0;        // thu tu dong lenh
    string input;        // du lieu tung dong lenh
    fstream fs;
    fs.open(filename, ios::in);
    while (!fs.eof())
    {
        getline(fs, input);
        result = split_string(input, num_words);
        line++;
        // lenh 1: iadd
        if (string(result[0]) == "iadd")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    stack.push(int(top_val + below_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 2: fadd
        else if (string(result[0]) == "fadd")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                stack.push(float(top_val + below_val), 1);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 3: isub
        else if (string(result[0]) == "isub")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    stack.push(int(below_val - top_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 4: fsub
        else if (string(result[0]) == "fsub")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();;
                below_val = stack.top_value();
                stack.pop();
                stack.push(float(below_val - top_val), 1);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 5: imul
        else if (string(result[0]) == "imul")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    stack.push(int(below_val * top_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 6: fmul
        else if (string(result[0]) == "fmul")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                stack.push(float(below_val * top_val), 1);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 7: idiv
        else if (string(result[0]) == "idiv")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    if (top_val == 0)
                    {
                        free_string(result, num_words);
                        stack.clear();
                        fs.close();
                        throw DivideByZero(line);
                    }
                    stack.push(int(below_val / top_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh  8: fdiv
        else if (string(result[0]) == "fdiv")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                if (top_val == 0)
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw DivideByZero(line);
                }
                stack.push(float(below_val / top_val), 1);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 9: irem
        else if (string(result[0]) == "irem")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    if (top_val == 0)
                    {
                        free_string(result, num_words);
                        stack.clear();
                        fs.close();
                        throw DivideByZero(line);
                    }
                    stack.push(int(below_val - (int)(below_val / top_val) * top_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 10: ineg
        else if (string(result[0]) == "ineg")
        {
            if (stack.size() >= 1)
            {
                if (stack.top_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    stack.push(int(-top_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 11:fneg
        else if (string(result[0]) == "fneg")
        {
            if (stack.size() >= 1)
            {
                top_val = stack.top_value();
                stack.pop();
                stack.push(float(-top_val), 1);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 12: iand
        else if (string(result[0]) == "iand")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    int bitwise = (int)top_val & (int)below_val;
                    stack.push(int(bitwise), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 13: ior
        else if (string(result[0]) == "ior")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    int bitwise = (int)top_val | (int)below_val;
                    stack.push(int(bitwise), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 14: ieq
        else if (string(result[0]) == "ieq")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    int tam = 0;
                    if (top_val == below_val)
                    {
                        tam = 1;
                    }
                    stack.push(int(tam), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 15: feq
        else if (string(result[0]) == "feq")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                int tam = 0;
                if (top_val == below_val)
                {
                    tam = 1;
                }
                stack.push(tam, 0);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 16: ineq
        else if (string(result[0]) == "ineq")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    int tam = 0;
                    if (top_val != below_val)
                    {
                        tam = 1;
                    }
                    stack.push(int(tam), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 17: fneq
        else if (string(result[0]) == "fneq")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                int tam = 0;
                if (top_val != below_val)
                {
                    tam = 1;
                }
                stack.push(tam, 0);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 18: ilt
        else if (string(result[0]) == "ilt")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    int tam = 0;
                    if (below_val < top_val)
                    {
                        tam = 1;
                    }
                    stack.push(int(tam), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 19: flt
        else if (string(result[0]) == "flt")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                int tam = 0;
                if (below_val < top_val)
                {
                    tam = 1;
                }
                stack.push(tam, 0);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 20 : igt
        else if (string(result[0]) == "igt")
        {
            if (stack.size() >= 2)
            {
                if (stack.top_type() == 0 && stack.below_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    below_val = stack.top_value();
                    stack.pop();
                    int tam = 0;
                    if (below_val > top_val)
                    {
                        tam = 1;
                    }
                    stack.push(int(tam), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 21: fgt
        else if (string(result[0]) == "fgt")
        {
            if (stack.size() >= 2)
            {
                top_val = stack.top_value();
                stack.pop();
                below_val = stack.top_value();
                stack.pop();
                int tam = 0;
                if (below_val > top_val)
                {
                    tam = 1;
                }
                stack.push(tam, 0);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 22: ibnot
        else if (string(result[0]) == "ibnot")
        {
            if (stack.size() >= 1)
            {
                if (stack.top_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    int tam = 0;
                    if (top_val == 0)
                    {
                        tam = 1;
                    }
                    stack.push(int(tam), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 23: iconst <val>
        else if (string(result[0]) == "iconst")
        {
            if (!stack.full())
            {
                stack.push(stoi(result[1]), 0);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackFull(line);
            }
        }
        // lenh 24: fconst <val>
        else if (string(result[0]) == "fconst")
        {
            if (!stack.full())
            {
                stack.push(stof(result[1]), 1);
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackFull(line);
            }
        }
        // lenh 25: iload <ind>
        else if (string(result[0]) == "iload")
        {
            if (stoi(result[1]) < 0 || stoi(result[1]) >= 256) 
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw ArrayOutOfRange(line);
            }
            else
            {
                if (array.check_index(stoi(result[1])))
                {
                    if ((int)array.type(stoi(result[1])) == 0)
                    {
                        if (!stack.full())
                        {
                            stack.push((int)array.value_at(stoi(result[1])), 0);
                        }
                        else
                        {
                            free_string(result, num_words);
                            stack.clear();
                            fs.close();
                            throw StackFull(line);
                        }
                    }
                    else
                    {
                        free_string(result, num_words);
                        stack.clear();
                        fs.close();
                        throw TypeMisMatch(line);
                    }
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw UndefinedVariable(line);
                }
            }
        }
        // lenh 26: fload <ind>
        else if (string(result[0]) == "fload")
        {
            if (stoi(result[1]) < 0 || stoi(result[1]) >= 256)
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw ArrayOutOfRange(line);
            }
            else
            {
                if (array.check_index(stoi(result[1])))
                {
                    if ((int)array.type(stoi(result[1])) == 1)
                    {
                        if (!stack.full())
                        {
                            stack.push((float)array.value_at(stoi(result[1])), 1);
                        }
                        else
                        {
                            free_string(result, num_words);
                            stack.clear();
                            fs.close();
                            throw StackFull(line);
                        }
                    }
                    else
                    {
                        free_string(result, num_words);
                        stack.clear();
                        fs.close();
                        throw TypeMisMatch(line);
                    }
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw UndefinedVariable(line);
                }
            }
        }
        // lenh 27: istore <ind>
        else if (string(result[0]) == "istore")
        {
            if (stoi(result[1]) < 0 || stoi(result[1]) >= 256)
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw ArrayOutOfRange(line);
            }
            else
            {
                if (!stack.empty())
                {
                    if ((int)stack.top_type() == 0)
                    {
                        top_val = stack.top_value();
                        stack.pop();
                        array.put_value((int)top_val, 0, stoi(result[1]));
                    }
                    else
                    {
                        free_string(result, num_words);
                        stack.clear();
                        fs.close();
                        throw TypeMisMatch(line);
                    }
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw StackEmpty(line);
                }
            }
        }
        // lenh 28: fstore <ind>
        else if (string(result[0]) == "fstore")
        {
            if (stoi(result[1]) < 0 || stoi(result[1]) >= 256)
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw ArrayOutOfRange(line);
            }
            else
            {
                if (!stack.empty())
                {
                    if ((int)stack.top_type() == 1)
                    {
                        top_val = stack.top_value();
                        stack.pop();
                        array.put_value((float)top_val, 1, stoi(result[1]));
                    }
                    else
                    {
                        free_string(result, num_words);
                        stack.clear();
                        fs.close();
                        throw TypeMisMatch(line);
                    }
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw StackEmpty(line);
                }
            }
        }
        // lenh 29: i2f
        else if (string(result[0]) == "i2f")
        {
            if (stack.size() >= 1)
            {
                if (stack.top_type() == 0)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    stack.push(float(top_val), 1);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 30: f2i
        else if (string(result[0]) == "f2i")
        {
            if (stack.size() >= 1)
            {
                if (stack.top_type() == 1)
                {
                    top_val = stack.top_value();
                    stack.pop();
                    stack.push(int(top_val), 0);
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw TypeMisMatch(line);
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 31: top
        else if (string(result[0]) == "top")
        {
            if (!stack.empty())
            {
                if (stack.top_type() == 1)
                {
                    cout << (float)stack.top_value() << "\n";
                }
                else
                {
                    cout << (int)stack.top_value() << "\n";
                }
            }
            else
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw StackEmpty(line);
            }
        }
        // lenh 32: val <ind>
        else if (string(result[0]) == "val")
        {
            if (stoi(result[1]) < 0 || stoi(result[1]) >= 256)
            {
                free_string(result, num_words);
                stack.clear();
                fs.close();
                throw ArrayOutOfRange(line);
            }
            else
            {
                if (array.check_index(stoi(result[1])))
                {
                    if (array.type(stoi(result[1])) == 0)
                    {
                        cout << (int)array.value_at(stoi(result[1])) << "\n";
                    }
                    else
                    {
                        cout << (float)array.value_at(stoi(result[1])) << "\n";
                    }
                }
                else
                {
                    free_string(result, num_words);
                    stack.clear();
                    fs.close();
                    throw UndefinedVariable(line);
                }
            }
        }
        free_string(result, num_words);
    }
}
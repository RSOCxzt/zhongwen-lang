#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define int long long
#define ull unsigned int
#define N 1048576
int memory[N],pos;
string code[N]={
};
void loadFile()
{
    string file;
    cout << "请输入脚本文件名(.zh)：";
    cin >> file;

    ifstream fin(file);
    if(!fin)
    {
        cout << "文件打开失败！\n";
        exit(0);
    }

    // 逐行读入 code 数组
    string line;
    int cnt = 0;
    while(getline(fin, line))
    {
        code[cnt++] = line;
        if(cnt >= N) break;
    }
    fin.close();
}
string readStr(int x,int y)	// 从 code[x][y] 开始读取一个字符串, 读到空格为止 
{
	pos=y;
	string ret="";
	int len=code[x].length();
	while(pos<len && code[x][pos]==' ')
	{
		++pos;
	}
	while(pos<len && code[x][pos]!=' ')
	{
		ret=ret+code[x][pos++];
	}
	return ret;
}

int readInt(int x,int y)
{
    pos=y;
    string line = code[x];
    int len=line.size();
    // 跳过空格
    while(pos<len && line[pos]==' ') pos++;

    bool neg = false;
    // 读取一段连续非空格字符串（中文数字整体）
    string token;
    while(pos<len && line[pos]!=' ')
    {
        token += line[pos];
        pos++;
    }

    // 先判断负号开头
    if(token.substr(0,2)=="负")
    {
        neg = true;
        token = token.substr(2);
    }

    // 中文数字映射表（全部英文逗号，删除超限大数单位垓、秭）
    unordered_map<string, long long> numMap = {
        {"零",0},{"一",1},{"二",2},{"三",3},{"四",4},{"五",5},
        {"六",6},{"七",7},{"八",8},{"九",9}
    };
    unordered_map<string, long long> unitMap = {
        {"十",10},{"百",100},{"千",1000},{"万",10000},{"亿",100000000},{"兆",1000000000000LL},{"京",10000000000000000LL}
    };

    bool isDigit = true;
    for(char ch : token)
    {
        if(!isdigit(ch) && ch!='-'){isDigit=false;break;}
    }
    if(isDigit)
    {
        long long res = stoll(token);
        return neg ? -res : res;
    }

    long long total = 0;
    long long curr = 0;
    int ptr = 0;
    int tokLen = token.size();
    while(ptr < tokLen)
    {
        string ch = token.substr(ptr, 2);
        if(numMap.count(ch))
        {
            curr = numMap[ch];
            ptr += 2;
        }
        else if(unitMap.count(ch))
        {
            if(curr == 0) curr = 1;
            total += curr * unitMap[ch];
            curr = 0;
            ptr += 2;
        }
        else break;
    }
    total += curr;
    return neg ? -total : total;
}

signed main()
{
	loadFile();
	for(int i=0;;i=(i+1)%N)
	{
		string op=readStr(i,0);
        // 初始化库标记 false
		bool fb[2] = {false, false};
		if(op=="引用"){
			// 修正读取参数起点，跳过操作符后的空格
			int p = op.size();
			while(p < code[i].size() && code[i][p] == ' ') p++;
			string f=readStr(i,p);
			if(f=="输入输出库"){
				fb[0]=true;
			}
			else if(f=="数学库")
			{
				fb[1]=true;
			}
		} 
		if(op=="输入"){
			if(!fb[0]){
				cout<<"错误：不包含必要库\n";
			} 
		}
	}
	return 0;
}

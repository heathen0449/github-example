#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

class token {
private:
	string name;
	int  order;
	string neirong;
public:
	token() {
		this->name = "***";
		this->order = 0;
		this->neirong = "FFF";
	}
	void setname(string e, string d) {
		this->name = e;
		this->neirong = d;

	}
	void set_num(int d)
	{
		this->order = d;
	}
	int get_nei(string n) {
		if (this->neirong == n)
			return 1;
		else
			return 0;
	}
	void show() {
		cout << "{" << " " << this->name  << ","<< this->order+1<< ","<<this->neirong<<" "<< "}" << endl;
	}


};
int main(void) {
	string code;
	int index;//����
	ifstream  file ("C:\\Users\\ljh0507\\Desktop\\a.cpp") ;//�ļ��������
	int state=1;//�Զ���״̬
	char dd;//��ǰ�������ַ�
	string wait;//��ǰԤ������
	string foofoo[19] = { "int","float","double","when","if","else","char","void","for","continue","do","while","return","swtich","case","break",
	"include","struct","main" };
	string fubuki[23] = { ";","+","-","*","/","<",">","{","}",">","<","=","==" ,"->",".",">=","<=",",","#","(",")" ,"[","]"};
	vector<token>IT, CT1,CT2, ST, KT, PT;
	int big;//��ʼ�������ַ��ָ�
	index = 0;
	int j;//���ڽ������
	token f;//�������token��������
	if (file.is_open()) {
		istreambuf_iterator<char> beg(file), end;//���϶�ȡ�����ļ��취
		string strdata(beg, end);
		code = strdata;
		while(index<=(code.length()-1)){
			switch (state) {
			case 1:
				while ((code[index]==0x20) || (code[index] == 0x09)||(code[index] == 0x0D)||(code[index]==0x0A)) {
					index++;
				}
				if (index > code.size())
				{
					cout << "С�ϵ�������������������" << endl;
					exit(0);
				}
				dd = code[index];
				big = index;
				if ((dd >= 0x41 && dd <= 0x5A) || (dd >= 0x61 && dd <= 0x7A))//������Ϊ��ĸ
				{
					state++;
					if(index<code.length()-1)
						index++;
				}
				else if (dd >= 0x30 && dd <= 0x39)//������Ϊ����
				{
					
					state = state + 2;
					if (index < code.length() - 1) {
						index++;
					}
				
				}
				else if (dd == 0x27) {
					state = state + 3;
					index++;
				}
				else if (dd == 0x22) {
					state = state + 4;
					index++;
				}
				else//���������֣����Զ���
				{
					j = index;
					while (code[j] != 0x0A && code[j] != 0x20&& code[j] != 0x09 && code[j]!=0x0D)//�γɽ������
					{
						if ((code[j] >= 0x41 && code[j] <= 0x5A) || (code[j] >= 0x61 && code[j] <= 0x7A) || (code[j] >= 0x30 && code[j] <= 0x39))
						{
							break;
						}
						if (j < code.length() - 1) {
							j++;
						}
						else {
							break;
						}
							
						
					}
					index = j;//����Ŀǰ����
					if(big==code.length()-1)
					wait = code.substr(big, 1);
					else {
						wait = code.substr(big, j-big);
					}
					int panju = 1;
					for (int fff = 0; fff < PT.size(); fff++) {   //�жϴ˽���Ƿ��Ѿ��ڽ��������
						if (PT[fff].get_nei(wait)) {
							panju = 0;
							PT[fff].show();//������ʾ���
							break;
						}
					}
					if (panju == 1) {  //��δ�ڣ��������Ӳ���
						int i;
						for (i = 0; i <= 22; i++) {
							if (fubuki[i] == wait) {
								f.setname("p", wait);
								PT.push_back(f);
								PT[PT.size() - 1].set_num(PT.size() - 1);
								PT[PT.size() - 1].show();
								break;
							}
						}
						
						if (i == 23) {
							cout << "error ����İ���ַ�" << wait << "��������" << endl;
							exit(0);
						}
					}
					index++;
				}
				break;
			case 2:
			{  
				
				j = index;
				string fff = "K";//�϶���Ϊ��ʶ�����ǹؼ���
				dd = code[index];
				if (code[j] == 0x0A || code[j] ==0x20 || code[j] ==0x09||code[j]==0x0D||index==code.length()-1)
				{   
					if (index == code.length() - 1)
						big = index;
					else
						big = index - 1;
					wait = code.substr(big, 1);
					int cc=0;
					if (IT.size()!=0)
					{
						for (cc = 0; cc <= IT.size() - 1; cc++) {
							if (IT[cc].get_nei(wait)) {
								IT[cc].show();
								break;
							}
						}
					}
					if (cc == IT.size())
					{
						f.setname("I", wait);
						IT.push_back(f);
						IT[IT.size() - 1].set_num(IT.size() - 1);
						IT[IT.size() - 1].show();
					}
					index++;
				}
				else {
					while ((code[j] >= 0x41 && code[j] <= 0x5A) || (code[j] >= 0x61 && code[j] <= 0x7A) || (code[j] >= 0x30 && code[j] <= 0x39)) {
						if (code[j] >= 0x30 && code[j] <= 0x39) {
							fff = "I"; 
						}
						if (code[j] == 0x20  ||code[j]==0x0A|| code[j] ==0x09||code[j]==0x0D)
						{
							break;
						}
						j++;
					}
					big = index - 1;
					wait = code.substr(big, j-big);
					if (fff == "K") {
						int aj;
						for (aj = 0; aj < KT.size(); aj++) {
							if (KT[aj].get_nei(wait)) {
								KT[aj].show();
								break;
							}
						}
						if (aj == int(KT.size())) {
							int gg;
							for (gg = 0; gg <= 18; gg++)
							{
								if (wait == foofoo[gg])
								{
									f.setname("K", wait);
									KT.push_back(f);
									KT[int(KT.size() - 1)].set_num(int(KT.size() - 1));
									KT[int(KT.size() - 1)].show();
									break;
								}
							}
							if (gg == 19)
							{
								fff = "I";
							}
						}
					}
					if(fff=="I"){
						
						int aj=0;
						if (IT.size() != 0)
						{
							for (aj = 0; aj <= IT.size() - 1; aj++) {
								if (IT[aj].get_nei(wait)) {
									IT[aj].show();
									break;
								}
							}
						}
						if (aj == IT.size()) {
							f.setname(fff, wait);
							IT.push_back(f);
							int pdd = IT.size() - 1;
							
							IT[pdd].set_num(pdd);
							IT[pdd].show();

						}
					}
					
					index = j;
				}
				state = 1;
				break;
			}
			case 3:
				
				j = index;
				if (index == code.length() - 1)
					big = index;
				else
					big = index - 1;
				while (code[j] >= 0x30 && code[j] <= 0x39) {
					j++;
				}
				if (code[j] == 0x2E) {
					state = state + 3;
					
				}
				else if (code[j] == 0x0D || code[j] == 0x0A || code[j] == 0x09 || code[j] == 0x20 || j == code.length() - 1) {
					wait = code.substr(big, 1);
					f.setname("C1", wait);
					CT1.push_back(f);
					CT1[CT1.size() - 1].set_num(CT1.size() - 1);
					CT1[CT1.size() - 1].show();
					index++;
					state = 1;
				}
				else {
					wait = code.substr(big, j - big);
					f.setname("C1", wait);
					CT1.push_back(f);
					CT1[CT1.size() - 1].set_num(CT1.size() - 1);
					CT1[CT1.size() - 1].show();
					index = j;
					state = 1;
				}
				break;
			case 4:
				
				j = index;
				if ((code[j] >= 0x41 && code[j] <= 0x5A) || (code[j] >= 0x61 && code[j] <= 0x7A) || (code[j] >= 0x30 && code[j] <= 0x39))
				{
					state = state + 3;
					index = j + 1;

				}
				else {
					cout << "������ִ���"<< endl;
					exit(0);
				}
				break;
			case 5:
				big = index - 1;
				j = index;
				if ((code[j] >= 0x41 && code[j] <= 0x5A) || (code[j] >= 0x61 && code[j] <= 0x7A) || (code[j] >= 0x30 && code[j] <= 0x39))
				{
					state = state + 3;
					index++;
				}
				else {
					cout << "ERROR" << endl;
					exit(0);
				}
				break;
			case 6:
				j=j+1;
				
				if (code[j] >= 0x30 && code[j] <= 0x39) {
					state = state + 3;
					j++;
					cout << "do" << endl;
				}
				else {
					cout << "ERROR"<<endl;
					state = 1;
					
				}
				break;
			case 7:
				j = index;
				
				if (code[index] == 0x27)
				{
					state = state + 3;
					if(index<code.length()-1)
					index++;
					else {
						index = index;
					}
				}
				else
				{
					cout << "error,�ַ���������" <<code[j]<< endl;
					exit(0);
				}
				break;
			case 8:
				j = index;
				while ((code[j] >= 0x41 && code[j] <= 0x5A) || (code[j] >= 0x61 && code[j] <= 0x7A) || (code[j] >= 0x30 && code[j] <= 0x39)) {
					j++;
				}
				
				if (code[j] == 0x22) {
					state = state + 3;
					index = j;
				}
				else {
					cout << "ERROR �ַ����������ִ���" << endl;
					exit(0);
				}
				break;
			case 9:
				while (code[j] >= 0x30 && code[j] <= 0x39) {
					j++;
				}
				wait = code.substr(big, j-big);
				cout << wait << endl;
				f.setname("C1", wait);
				CT1.push_back(f);
				CT1[CT1.size() - 1].set_num(CT1.size() - 1);
				CT1[CT1.size() - 1].show();
				index = j;
				state = 1;
				break;
			case 10:
				if (index == code.length() - 1)
					wait = code.substr(big, index - big +1);
				else
					wait = code.substr(big, index - big);
				f.setname("C2", wait);
				CT2.push_back(f);
				CT2[CT2.size() - 1].set_num(CT2.size() - 1);
				CT2[CT2.size() - 1].show();
				state = 1;
				index++;
				break;
			case 11:
				index++;
				if (index == code.length() - 1)
					wait = code.substr(big, index - big + 1);
				else
					wait = code.substr(big, index - big);
				f.setname("S", wait);
				ST.push_back(f);
				ST[ST.size() - 1].set_num(ST.size() - 1);
				ST[ST.size() - 1].show();
				state = 1;
				index++;
				break;
			}
		}
	}
	else
	{
		cout << "file open error" << endl;
	}	
	file.close();
	return 0;
}
#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<string>
#include<list>
#include <fstream>
#include"Word_divider.h"
using namespace std;

class analyzer {

public:

	analyzer() {
		word_stack.push("#");
		lookhead = 0;

	}
	~analyzer() {

	}

	void program() {//program -> declaration-list statements
		word_stack.push("statements");//���
		word_stack.push("declaration-list");//����
		cout << "program->declaration - list statements" << endl;
		declaration_list();
		statements();

	}

private:
	void declaration_list() {//declaration-list ->var-declaration declaration-list |��
		if (lookhead < Processing_complete.size() && (Processing_complete.at(lookhead).compare("int")==0 || Processing_complete.at(lookhead).compare("double") == 0) ){
			word_stack.pop();
			word_stack.push("declaration-list");
			word_stack.push("var-declaration");
			cout << "declaration-list ->var-declaration declaration-list" << endl;
			var_declaration();
			declaration_list();
		}
		else {
			word_stack.pop();
			cout << "declaration-list ->��" << endl;
		}
	}
	void var_declaration() {//var-declaration -> type-specifier id-list ; ����
		word_stack.pop();
		word_stack.push(";");
		word_stack.push("id-list");
		word_stack.push("type-specifier");
		cout << "var-declaration -> type-specifier id-list ;" << endl;
		type_specifier();
		id_list();
		if (Processing_complete.at(lookhead).compare(";")==0) {
			word_stack.pop();
			lookhead++;
		}
	}
	void type_specifier() {//type-specifier -> int | double ����
		if (Processing_complete.at(lookhead).compare("int") == 0) {
			lookhead++;
			cout << "type-specifier -> int" << endl;
			word_stack.pop();
		}
		else if (Processing_complete.at(lookhead).compare("double") == 0) {
			lookhead++;
			cout << "type-specifier -> double" << endl;
			word_stack.pop();
		}
	}
	void id_list() {//id-list -> ID list-tail
		word_stack.pop();
		word_stack.push("list-list");
		word_stack.push("ID");
		cout << "id-list -> ID list-tail" << endl;
		if (Processing_complete.at(lookhead).compare("id")==0) {
			word_stack.pop();
			lookhead++;
		}
		list_tail();
	}

	void list_tail() {//list-tail -> , ID list-tail |��
		if (Processing_complete.at(lookhead).compare(",") == 0) {
			word_stack.pop();
			word_stack.push("list-tail");
			word_stack.push("ID");
			lookhead++;
			if (Processing_complete.at(lookhead).compare("id")==0) {
				word_stack.pop();
				lookhead++;
			}
			cout << "list-tail -> , ID list-tail" << endl;
			list_tail();
		}
		else {
			word_stack.pop();
			cout<<"list-tail -> ��"<<endl;
		}
	}

	 void statements() {//statements -> statement ; statements |�� 
		bool flag = false;
		for (int n = lookhead ; n < Processing_complete.size(); n++) {
			if (Processing_complete.at(n).compare(";")==0) {
				flag = true;
				break;
			}
		}
		if (flag == true) {
			word_stack.pop();
			word_stack.push("statements");
			word_stack.push(";");
			word_stack.push("statement");
			cout<<"statements -> statement ; statements"<<endl;
			statement();
			if (Processing_complete.at(lookhead).compare(";")==0) {
				word_stack.pop();
				lookhead++;
			}
			statements();
		}
		else {
			word_stack.pop();
			cout<<"statements -> ��"<<endl;
		}

	}

	void statement() {//statement -> assign_statement
		word_stack.pop();
		word_stack.push("assign_statement");
		cout << "statement -> assign_statement"<<endl;
		assign_statement();
	}

	void  assign_statement() {//assign_statement -> ID = expr ��ֵ���
		word_stack.pop();
		word_stack.push("expr");
		word_stack.push("=");
		word_stack.push("ID");
		cout<<"assign_statement -> ID = expr"<<endl;
		if (Processing_complete.at(lookhead).compare("id")==0) {
			word_stack.pop();
			lookhead++;
			if (Processing_complete.at(lookhead).compare("=")==0) {
				word_stack.pop();
				lookhead++;
			}
		}
		expr();
	}

	void expr() {//expr -> term expr1 ���ʽ
		word_stack.pop();
		word_stack.push("expr1");
		word_stack.push("term");
		cout<<"expr -> term expr1"<<endl;
		term();
		expr1();
	}

	void expr1() {//expr1 -> +term expr1 | -term expr1 |��
		word_stack.pop();
		if (Processing_complete.at(lookhead).compare("+")==0) {
			word_stack.push("expr1");
			word_stack.push("term");
			cout<<"expr1 -> +term expr1"<<endl;
			lookhead++;
			term();
			expr1();
		}
		else if (Processing_complete.at(lookhead).compare("-")==0) {
			word_stack.push("expr1");
			word_stack.push("term");
			cout<<"expr1 -> -term expr1"<<endl;
			lookhead++;
			term();
			expr1();
		}
		else {

			cout<<"expr1 -> ��"<<endl;
		}

	}

	void term() {// term -> factor term1 ����
		word_stack.pop();
		word_stack.push("term1");
		word_stack.push("factor");
		cout << "term -> factor term1"<<endl;
		factor();
		term1();
	}

	void term1() {//term1 -> *factor term1 | /factor term1 |��
		if (Processing_complete.at(lookhead).compare("*")==0) {
			word_stack.pop();
			word_stack.push("term1");
			word_stack.push("factor");
			cout<<"term1 -> *factor term1"<<endl;
			lookhead++;
			factor();
			term1();
		}
		else if (Processing_complete.at(lookhead).compare("/")==0) {
			word_stack.pop();
			word_stack.push("term1");
			word_stack.push("factor");
			cout<<"term1 -> /factor term1"<<endl;
			lookhead++;
			factor();
			term1();
		}
		else {
			word_stack.pop();
			cout<<"term1 -> ��"<<endl;
		}
	}

	void factor() {//factor -> (expr) | ID | NUM ����
		if (Processing_complete.at(lookhead).compare("(")==0) {
			word_stack.pop();
			word_stack.push(")");
			word_stack.push("expr");
			cout<<"factor -> (expr)"<<endl;
			lookhead++;
			expr();
			if (Processing_complete.at(lookhead).compare(")")==0) {
				word_stack.pop();
				lookhead++;
			}
		}
		else if (Processing_complete.at(lookhead).compare("id")==0) {
			word_stack.pop();
			lookhead++;
			cout<<"factor -> ID"<<endl;
		}
		else if (Processing_complete.at(lookhead).compare("num")==0) {
			word_stack.pop();
			lookhead++;
			cout<<"factor -> NUM"<<endl;
		}
	}


	// void main(String[] args) {
	//	String path_in = "D:\\test.txt"; // ������Ϣ�ļ�·��
	//	Recursivedescent r = new Recursivedescent();
	//	r.analyzer = new An(); // ����һ���ʷ�������
	//	String p_in = r.analyzer.pretreatment(path_in);// p_inΪ����Ԥ�������ı���Ϣ(������Ԥ������)
	//	r.analyzer.scanner(p_in);
	//	for (int i = 0; i < r.analyzer.name.size(); i++) {//�����дʽ��з���
	//		cout<<r.analyzer.name.get(i) + " " + r.Processing_complete.at(i));
	//	}

	//	r.program();
	//	if (r.s.isEmpty()) {
	//		cout<<"��ȷ"<<endl;
	//	}
	//	else {
	//		cout<<"����"<<endl;
	//		cout<<r.s);
	//	}
	//}






	

public:
	vector<string> Processing_complete;

	stack<string> word_stack;
	int lookhead = 0;
};





int main() {

	string str;
	string wait_analyzer;
	const string file_path("../test.txt");

	ifstream ifs;
	ifs.open(file_path,ios::in);


	while (getline(ifs,str)) {
		
		wait_analyzer.append(str);
	}

	ifs.close();

	analyzer anal;



	Word_divier(wait_analyzer, anal.Processing_complete);

	anal.program();

	if (anal.word_stack.top().compare("#") == 0)
		cout << "������ȷ" << endl;
	else
		cout << "����ʧ��" << endl;
	



}
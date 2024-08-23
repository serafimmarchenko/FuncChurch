#include <iostream>
#include <vector>
#include "string.h"
#include <map>

using namespace std;

enum class TT {
	Var = 0,
	Const = 1,
	Func = 2,
	newFunc = 3,
	Func = 4
};

class mTerm{
	public:
		string name;
		
		mTerm(string name) : name (name) {};
};
map<string, mTerm*> terms;

class mToken: public mTerm{
	public:
		TT type;
		vector<mTerm*> args;
		mToken(string name, TT type) : mTerm::mTerm(name), type(type) {};
};

class Func: public mTerm{
	public:
		vector<mTerm*> args;
		mToken body;
		Func(string name, vector<mTerm*> args, mToken body) : mTerm(name), args(args), body(body) {};
};

vector<mToken> lexer(string code) {
	vector<mToken> res;
	string word = "";
	int num = 0;
	TT type = TT::Var;
	for (char c : code) {
		if (isdigit(c)) {
			num = num*10+(c-'0');
		}
		else if (c == 'L' && word == "") {
			type = TT::newFunc;
		}
	}
	return res;
}

mToken parse(vector<mToken> code) {
	for (mToken i : code) {
		
	}
	mToken res("main", TT::Func);
	return res;
}

void run(mToken* token, vector<Func>* funcs) {
	switch(token->type){
		case TT::Func:
			for(mTerm* a : token->args) {
				if (token->type = TT::Var)
					continue;
				else if (token->type = TT::Const)
					continue;
				else if (token->type = TT::Func)
					continue;
				else
					*a = run(a, funcs);
			}
			return token->call();
		case TT::newFunc:
			return mToken("bla", TT::Func);
	}
}

int main() {
	cout << "Hello Lambda!" << endl;
	cout << "Write you functions here!" << endl;
	vector<Func> funcs = {};
	while (true) {
		cout << ">> ";
		string code;
		getline(cin, code);
		vector<mToken> lexed = lexer(code);
		mToken parsed = parse(lexed);
		run(&parsed);
	}
	return 0;
}

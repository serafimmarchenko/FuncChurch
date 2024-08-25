#include <iostream>
#include <vector>
#include "string.h"
#include <map>

using namespace std;

enum class TT {
	Undef = 0,
	Var = 1,
	Const = 2,
	Func = 3,
	newFunc = 4,
	nameFunc = 5,
	setFunc = 6
};

class mTerm{
	public:
		string name;
		
		mTerm(string name) : name (name) {};
};
map<string, mTerm*> terms;

class mToken : public mTerm{
	public:
		TT type;
		vector<mTerm*> args;
		mToken(string name, TT type) : mTerm::mTerm(name), type(type) {};
};

class Func : public mTerm{
	public:
		static string setName = "";
		vector<mTerm*> args;
		mToken body;
		Func(string name, vector<mTerm*> args, mToken body) : mTerm(name), args(args), body(body) {};
		string call(vector<mTerm*> args);
};

vector<mToken> lexer(string code) {
	vector<mToken> res;
	string word = "";
	TT type = TT::Undef;
	for (char c : code) {
		if (isdigit(c)) {
			num = num*10+(c-'0');
			type
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

mToken* put_args(Func* f, vector<mTerm*> args) {
	
}

void run(mToken* token, vector<Func>* funcs) {
	switch(token->type){
		case TT::Func:
			token = static_cast<Func*>(token);
			for(mTerm* a : token->args) {
				if (token->type = TT::Var)
					continue;
				else if (token->type = TT::Const)
					continue;
				else if (token->type = TT::Func)
					continue;
				else if (token->type = TT::nameFunc)
					continue;
				else
					*a = run(a, funcs);
			}
			new_token = put_args(token, token->args); // It's token, in which args was put on their places.
			run(put_args(new_token->body, token->args), funcs);
			delete new_token;
		case TT::newFunc:
			if (token->args[0] == "set") {
				(*funcs).push_back(Func(Func::setName, token->args[1], token->args[2]));
			}
			else {
				(*funcs).push_back(Func(token->args[0], token->args[1], token->args[2]));
			}
			cout "#New func was made";
		case TT::setFunc:
			Func::setName = token->args[0];
			run(token->args[1], funcs);
			
			cout << "#New func was set";
		default:
			cout << token->name;
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

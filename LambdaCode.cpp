#include <iostream>
#include <vector>
#include "string.h"
#include <map>

using namespace std;

enum class TT {
	Undef = 0,
	Var = 1,
	Const = 2,
	nameFunc = 3,
	Func = 4,
	newFunc = 5,
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
		vector<mTerm> args;
		mToken(string name, TT type) : mTerm::mTerm(name), type(type) {};
};

class Func : public mTerm{
	public:
		static string setName = "";
		vector<mTerm*> fargs;
		mToken body;
		Func(string name, vector<mTerm> args, mToken body) : mTerm(name), fargs(args), body(body) {};
		string call(vector<mTerm*> args);
};

vector<mToken> lexer(string code) {//Here will be code.
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

mToken parse(vector<mToken> code) {//Here will be code.
	for (mToken i : code) {
		
	}
	mToken res("main", TT::Func);
	return res;
}

mToken* put_args(Func* f, *vector<mTerm> args) {
	map<mTerm, mTerm> replace;
	for (int i = 0; i < f->args.size(); ++i) {
		replace[f->fargs[i].name] = (*args)[i].name;
	}
	mToken new_body = f->body;
	//Here will be code for replacing names of arguments with args.
	return new_body;
}

mToken run(mToken* token, vector<Func>* funcs) {
	switch(token->type){
		case TT::Func:
			token = static_cast<Func*>(token);
			for(mTerm& a : token->args) {
				if (a.type = TT::Var)
					continue;
				else if (a.type = TT::Const)
					continue;
				else if (a.type = TT::Func)
					continue;
				else if (a.type = TT::nameFunc)
					continue;
				else
					a = run(&a, funcs);
			}
			new_body = put_args(token, token->args); // It's body, in which args was put on their places
			return run(new_body, funcs);
		case TT::newFunc:
			string name = (token->args[0] == "set") ? Func::setName : token->args[0];
			(*funcs).push_back(Func(name, token->args[1], token->args[2]));
			
			cout << "#New func was made" << endl;
			return mToken(name, TT::nameFunc);
		case TT::setFunc:
			Func::setName = token->args[0];
			run(static_cast<mToken*>(&(token->args[1])), funcs);
			Func::setName = "";
			cout << "#New func was set" << endl;
			return mTerm("#N");
		default:
			return token;
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
		mTerm res = run(&parsed);
		if (res.name != "#N"){
			cout << res.name;
	}
	return 0;
}

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

	Apply = 4,
	newFunc = 5,
	setFunc = 6,

	Oper = 7,
	Name = 8
};

class mTerm{
	public:
		string name;
		TT type;
		mTerm(string name, TT type) : name {name}, type{type} {};
};
//map<string, mTerm> terms{}; I'm not sure that it is needed.

class mOper : public mTerm {
	public:
		TT type;
		vector<mTerm> args;
		mToken(string name, TT type) : mTerm::mTerm(name), type(type) {};
};

class Func : {
	public:
		static string setName = "";
		string name;
		vector<mTerm> args;
		vector<mTerm> body;
		Func(string name, vector<mTerm> args, mOper body) : mTerm(name), fargs(args), body(body) {};
};

vector<mToken> lexer(string code) {
	vector<mTerm> res;
	string word = "";
	TT type = TT::Undef;
	for (char c : code) {
		if (c == ' ' && word.size()) {
			if (word == "=")
				res.push_back(mTerm("=", TT::Oper));
			if (word == ":")
				res.push_back(mTerm(":", TT::Oper));
			else
				res.push_back(mTerm(word, type));
			continue;
		}
		else if (c == ' ')
			continue;
		
		word += c;
		if (type)
			continue;
		else if (isdigit(c))
			type = TT::Const;
		else if (isalpha(c))
			type = TT::Name;
		else 
			type = TT::Oper;
	}
	return res;
}

mToken parse(vector<mToken> code) {//Here will be code.
	for (mToken i : code) {
		
	}
	mToken res("main", TT::Func);
	return res;
}

mToken* put_args(Func* f, vector<mTerm>* args) {
	map<string, mTerm> replace;
	for (int i = 0; i < f->args.size(); ++i) {
		replace[f->fargs[i].name] = (*args)[i];
	}
	vector<mTerm>* exe_mod = new vector<mTerm>(f->body);// Is it work?
	//Here will be code for replacing names of arguments with args.
	for (int i = 0; i < exe_mod->size(); ++i) {
		if (replace.find(*exe_mod[i].name) == replace.end())
			continue;
		else {
			*exe_mod[i] = replace[*exe_mod[i].name];
		}
	}
	return exe_mod;
}

mToken run(mToken* token, vector<Func>* funcs) { // Correct it because of new architecture!
	switch(token->type){
		case TT::Apply:
			token = static_cast<Func*>(token);
			for(mTerm& a : token->args) {
				if (a.type = TT::Var)
					continue;
				else if (a.type = TT::Const)
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

#ifndef HAHA_LANGUAGE_INTERPRETER_H_
#define HAHA_LANGUAGE_INTERPRETER_H_

namespace interpreter{
	
	struct token {
		string keyword, name, value;
		int int_value=0;
		};
		
	struct loop_construct {
		string line;
		token new_token;
		};
		
	//Remove this heresy later
	//vector<token> token_vector;
	
	/*
	- ha = integer
	- ah = string
	- haha = print literal
	- hahaha = print var
	- hhaa = input
	- h = newline
	- aah = system
	- aha = arithmetic
	- a = increment/decrement 
	- haa = if
	- haahaa = loop
	- he = end if
	- hehe = end loop
	*/
	
	vector<token> integer_variables;
	vector<token> string_variables;
	vector<loop_construct> loop_vector;
	bool if_flag_skipper=false;
	bool loop_flag=false;
	int loop_number=1;
	int *loop_number_ptr=&loop_number;
	
	void process_token(token& token_input,string text_line){
		regex first_word_pattern("^\\w+");
		regex second_word_pattern("^\\w+\\s+(\\w+)");
		regex secondAll_word_pattern("^\\w+\\W+([\\w\\W]+)");
		regex secondAllnumber_word_pattern("^\\w+\\W+(\\d+)");
		regex second_thirdnumber_word_pattern("^\\w+\\W+(\\d+)\\s(\\w+)");
		regex second_third_word_pattern("^\\w+\\W+(\\w+)\\W+(\\w+)");
		regex second_third_math_pattern("^\\w+\\s+(\\+\\+|--)\\s+(\\w+)");
		regex second_all_word_pattern("^\\w+\\W+(\\w+)\\s+([\\w\\W]+)");
		regex condition_checker("^\\w+\\s(\\w+)\\s([=|<|>|!])\\s(\\w+)");
		regex math_checker("^\\w+\\s(\\w+)\\s([\\+|-|\\*|\\/])\\s(\\w+)\\s(\\w+)");
		
		smatch matched_keyword;
		
		
		
		if(loop_flag){
			loop_construct new_loop;
			new_loop.line = text_line;
			new_loop.new_token = token_input;
			loop_vector.push_back(new_loop);
			}
		
		
		//if
		regex_search(text_line,matched_keyword,first_word_pattern);
				if(matched_keyword.str()=="he") if_flag_skipper=false;
				if(if_flag_skipper) {return;}
		
		
		
		// int
		if(token_input.keyword=="ha"){
			regex_search(text_line,matched_keyword,second_third_word_pattern);
			token_input.name=matched_keyword.str(1);
			token_input.value=matched_keyword.str(2);			token_input.int_value=stoi(matched_keyword.str(2));
			//check first
			for(auto i : integer_variables){
				if(i.name==token_input.name){
					cout<<"Error: An integer variable named '"<<i.name<<"' already exists.";
					exit(1);
					}
				}
			integer_variables.push_back(token_input);
			}
			
			// string
		else if(token_input.keyword=="ah"){
			regex_search(text_line,matched_keyword,second_all_word_pattern);
			token_input.name=matched_keyword.str(1);
			token_input.value=matched_keyword.str(2);
			for(auto i : string_variables){
				if(i.name==token_input.name){
					cout<<"Error: A string variable named '"<<i.name<<"' already exists.";
					exit(1);
					}
				}
			string_variables.push_back(token_input);
			}
			
			//print literal
		else if(token_input.keyword=="haha"){
			regex_search(text_line,matched_keyword,secondAll_word_pattern);
			cout<<matched_keyword.str(1).c_str();
			}
			
		else if(token_input.keyword=="h"){
			regex_search(text_line,matched_keyword,secondAllnumber_word_pattern);
			for(int i=0; i<stoi(matched_keyword.str(1)); ++i)
			cout<<endl;
			}
		
		//print var
		else if(token_input.keyword=="hahaha"){
			regex_search(text_line,matched_keyword,second_word_pattern);
			for(auto i : integer_variables){
				if(i.name==matched_keyword.str(1)){
					i.value=to_string(i.int_value);
					cout<<i.value;
					return;
					}
				}
			for(auto i : string_variables){
					if(i.name==matched_keyword.str(1)){
					cout<<i.value;
					return;
					}
				}
			}
			
		else if(token_input.keyword=="hhh"){
				regex_search(text_line,matched_keyword,second_thirdnumber_word_pattern);
				int number_limit=stoi(matched_keyword.str(1));
				for(auto &i : integer_variables){
					if(i.name==matched_keyword.str(2)){
						i.int_value=rand()%number_limit+1;
						i.value=to_string(i.int_value);
						return;
						}
					}
				}
			
			
			
		else if(token_input.keyword=="aah"){
			regex_search(text_line,matched_keyword,secondAll_word_pattern);
			system(matched_keyword.str(1).c_str());
			}
		
		else if(token_input.keyword=="a"){
			regex_search(text_line,matched_keyword,second_third_math_pattern);
			for(auto &i : integer_variables){
				if(matched_keyword.str(2)==i.name){
					
					if(matched_keyword.str(1)=="++"){
					++i.int_value;
					i.value = to_string(i.int_value);
					}
					else if(matched_keyword.str(1)=="--"){
					--i.int_value;
					i.value = to_string(i.int_value);}
					else {cout<<"Something's wrong with the operator."; exit(0);}
					return;
					}
				}
			}
			
		else if(token_input.keyword=="haa"){
			regex_search(text_line,matched_keyword,condition_checker);
			string x="",y="";
			int nx=0,ny=0;
			for(auto i : integer_variables){
				if(i.name==matched_keyword.str(1)){
					x=i.value;
					nx=i.int_value;}
				if(i.name==matched_keyword.str(3)){
					y=i.value;
					ny=i.int_value;}
				}
			for(auto i : string_variables){
				if(i.name==matched_keyword.str(1))
					x=i.value;
				if(i.name==matched_keyword.str(3))
					y=i.value;
				}
				
				if(matched_keyword.str(2)=="="){
					if(nx!=ny) if_flag_skipper=true;
					if(x!=y) if_flag_skipper=true;
					return;
					}
				else if(matched_keyword.str(2)==">"){
					if(!(stoi(x)>stoi(y))) if_flag_skipper=true;
					return;
					}
				else if(matched_keyword.str(2)=="<"){
					if(!(stoi(x)<stoi(y))) if_flag_skipper=true;
					return;
					}
			}
		
		else if(token_input.keyword=="hhaa"){
			regex_search(text_line,matched_keyword,second_word_pattern);
			
			for(auto &i : integer_variables){
				if(i.name==matched_keyword.str(1)){
					cin>>i.int_value;
					i.value=to_string(i.int_value);
					return;
					}
				}
			for(auto &i : string_variables){
				if(i.name==matched_keyword.str(1)){
					cin>>i.value;
					}
				}
			}
		
		else if(token_input.keyword=="haahaa"){
			regex_search(text_line,matched_keyword,second_word_pattern);
			loop_flag=true;
			for(auto i : integer_variables){
				if(i.name==matched_keyword.str(1)){
					loop_number=i.int_value;
					}
				}
			
			
			}
		
		else if(token_input.keyword=="hehe"){
			loop_flag=false;
			if(loop_number<=1) {
				loop_vector.clear();
				return;
				}
			for(int i=1; i<*loop_number_ptr; ++i){
			for(auto& i : loop_vector){
				if(i.new_token.keyword=="hehe") continue;
				process_token(i.new_token,i.line);
					}
				}
			loop_vector.clear();
			}
		
		else if(token_input.keyword=="aha"){
			regex_search(text_line,matched_keyword,math_checker);
			int x,y,*z;
			string *result_string;
			for(auto &i : integer_variables){
				if(i.name==matched_keyword.str(1))
					x=i.int_value;
				if(i.name==matched_keyword.str(3))
					y=i.int_value;
				if(i.name==matched_keyword.str(4))
					z=&i.int_value;
					result_string=&i.value;
				}
				
				if(matched_keyword.str(2)=="+"){
					*z=x+y;
					*result_string=to_string(*z);
					return;
					}
				else if(matched_keyword.str(2)=="-"){
					*z=x-y;
					*result_string=to_string(*z);
					return;
					}
				else if(matched_keyword.str(2)=="*"){
					*z=(x) * (y);
					*result_string=to_string(*z);
					return;
					}
				else if(matched_keyword.str(2)=="/"){
					*z=(x) / (y);
					*result_string=to_string(*z);
					return;
					}
					
				
			}
		
		else {
			//Do nothing, this is just comment lol
			}
	}
	
	void read_tokens(string file_name){
		ifstream file(file_name.c_str());
		
		if(file.is_open()){
			string text_line, token_keyword, token_name, token_value;
			regex pattern("^\\w+");
			smatch matched_keyword;
			
			while(getline(file,text_line)){
				token new_token;
				
				//text_line+='\n';
				
				regex_search(text_line,matched_keyword,pattern);
				
				new_token.keyword = matched_keyword.str();

				process_token(new_token,text_line);
			}
			
		} else {
			cout<<"Can't open file for some reason.";
		}
		
		
		}
	
}
	
#endif

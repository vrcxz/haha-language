#ifndef HAHA_LANGUAGE_LEXER_H_
#define HAHA_LANGUAGE_LEXER_H_

namespace lexer{
	
	struct token {
		string keyword, name, value;
		int int_value=0;
		};
	
	struct loop_construct {
		token new_token;
		string text_line;
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
	- a = increment/decrement 
	- haa = if
	- haahaa = loop
	- he = end if
	- hehe = end loop
	- hhh = random
	*/
	
	vector<token> integer_variables;
	vector<token> string_variables;
	vector<token> loop_vector;
	bool if_flag_skipper=false;
	bool loop_flag=false;
	
	void process_token(token& token_input,string text_line){
		regex second_word_pattern("^\\w+\\s+(\\w+)");
		regex secondAll_word_pattern("^\\w+\\W+([\\w\\W]+)");
		regex secondAllnumber_word_pattern("^\\w+\\W+(\\d+)");
		regex second_third_word_pattern("^\\w+\\W+(\\w+)\\W+(\\w+)");
		regex second_third_math_pattern("^\\w+\\s+(\\+\\+|--)\\s+(\\w+)");
		regex second_all_word_pattern("^\\w+\\W+(\\w+)\\s+([\\w\\W]+)");
		regex condition_checker("^\\w+\\s(\\w+)\\s([=|<|>|!])\\s(\\w+)");
		
		smatch matched_keyword;
		
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
			string x,y;
			for(auto i : integer_variables){
				if(i.name==matched_keyword.str(1))
					x=i.value;
				if(i.name==matched_keyword.str(3))
					y=i.value;
				}
			for(auto i : string_variables){
				if(i.name==matched_keyword.str(1))
					x=i.value;
				if(i.name==matched_keyword.str(3))
					y=i.value;
				}
				
				if(matched_keyword.str(2)=="="){
					if(x!=y) if_flag_skipper=true;
					return;
					}
				else if(matched_keyword.str(2)==">"){
					if(!(x>y)) if_flag_skipper=true;
					return;
					}
				else if(matched_keyword.str(2)=="<"){
					if(!(x<y)) if_flag_skipper=true;
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
			
			}
		
		//check for variable names
		else {}
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
				if(new_token.keyword=="he") if_flag_skipper=false;
				if(if_flag_skipper)continue;
				process_token(new_token,text_line);
			}
			
		} else {
			cout<<"Can't open file for some reason.";
		}
		
		
		}
	
}
	
#endif

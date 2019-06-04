#include <iostream>
#include <stack>
#include <set>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;
struct R
{
	string name;
	string head;
	string tail;
};
struct CMOS
{
	string Mname;
	string D;
	string G;
	string S;
	string B;
	string Type;
};
set<char> nots;
CMOS cmos[100];
CMOS NOTArray[100];
R    rr[100];
int wirecount = 0;
int counter = 0;
int rCounter = 0;
int notcounter = 0;
string up;
string down;
string finalExp;
string exp1;

string remover();
R ANDp(string one, string two);
R ORp(string one, string two);
string priority(string);
void NOT(string exp);
void replaceWires(string a, string b);
string PUN(string postFix);
string removeNots(string exp);
string bracketNots(int i);
R findR(string Rname)
{
	R r;
	for (int i = 0; i < 100; i++)
	{
		if (rr[i].name == Rname)
		{
			r = rr[i];
			i = 100;
		}
	}
	return r;
}
R ANDp(string one, string two)
{
	R current;
	R current2;
	R returnstruct;
	if (one[0] != 'r' && two[0] != 'r')
	{
		if (one.length() == 1)
			one += "Not";
		else
			one = one[0];
		if (two.length() == 1)
			two += "Not";
		else
			two = two[0];
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = "W";
		cmos[counter].S += to_string(wirecount);
		cmos[counter].B = cmos[counter].S;
		wirecount++;
		cmos[counter].G = one;
		cmos[counter].Type = "PMOS";
		cmos[counter].D = "W";
		cmos[counter].D += to_string(wirecount);
		wirecount++;
		counter++;
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = cmos[counter - 1].D;
		cmos[counter].B = cmos[counter - 1].D;
		cmos[counter].G = two;
		cmos[counter].Type = "PMOS";
		cmos[counter].D = "W";
		cmos[counter].D += to_string(wirecount);
		returnstruct.head = cmos[counter - 1].S;
		returnstruct.tail = cmos[counter].D;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		wirecount++;
		counter++;
		return returnstruct;
	}

	else if (one[0] == 'r' && two[0] != 'r')
	{

		if (two.length() == 1)
			two += "Not";
		else
			two = two[0];
		current = findR(one);
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = current.tail;
		cmos[counter].B = current.tail;
		cmos[counter].G = two;
		cmos[counter].Type = "PMOS";
		cmos[counter].D = "W";
		cmos[counter].D += to_string(wirecount);
		returnstruct.head = current.head;
		returnstruct.tail = cmos[counter].D;
		wirecount++;
		counter++;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		return returnstruct;
	}
	else if (one[0] != 'r' && two[0] == 'r')
	{
		if (one.length() == 1)
			one += "Not";
		else
			one = one[0];
		current = findR(two);
		// !r
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = "W";
		cmos[counter].S += to_string(wirecount);
		cmos[counter].B = cmos[counter].S;
		wirecount++;
		cmos[counter].G = one;
		cmos[counter].Type = "PMOS";
		cmos[counter].D = current.head;

		returnstruct.tail = current.tail;
		returnstruct.head = cmos[counter].S;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		wirecount++;
		counter++;
		return returnstruct;

	}
	else if (one[0] == 'r' && two[0] == 'r')
	{
		current = findR(one);
		current2 = findR(two);
		returnstruct.head = current.head;
		returnstruct.tail = current2.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		replaceWires(current.tail, current2.head);
		rr[rCounter] = returnstruct;
		rCounter++;
		return returnstruct;
	}
}
R ORp(string one, string two)
{
	R current;
	R current2;
	R returnstruct;
	if (one[0] != 'r' && two[0] != 'r')
	{
		if (one.length() == 1)
			one += "Not";
		else
			one = one[0];
		if (two.length() == 1)
			two += "Not";
		else
			two = two[0];
		cmos[counter].Mname = "MQ";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = "W";
		cmos[counter].S += to_string(wirecount);
		cmos[counter].B = cmos[counter].S;
		cmos[counter].G = one;
		cmos[counter].D = "W";
		cmos[counter].D += to_string(1 + wirecount);
		cmos[counter].Type = "PMOS";

		cmos[counter + 1].Mname = "MQ";
		cmos[counter + 1].Mname += to_string(2 + counter);
		cmos[counter + 1].S = "W";
		cmos[counter + 1].S += to_string(wirecount);
		cmos[counter + 1].B = cmos[counter + 1].S;
		cmos[counter + 1].G = two;
		cmos[counter + 1].D = "W";
		cmos[counter + 1].D += to_string(wirecount + 1);
		cmos[counter + 1].Type = "PMOS";
		returnstruct.head = cmos[counter + 1].S;
		returnstruct.tail = cmos[counter + 1].D;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		wirecount += 2;
		counter += 2;
		return returnstruct;
	}
	else if (one[0] == 'r' && two[0] == 'r')
	{
		for (int i = 0; i < 100; i++)
		{
			if (rr[i].name == one)
			{
				current = rr[i];
				i = 100;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (rr[i].name == two)
			{
				current2 = rr[i];
				i = 100;
			}
		}
		returnstruct.head = current.head;
		returnstruct.tail = current.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		replaceWires(current.tail, current2.tail);
		replaceWires(current.head, current2.head);
		rr[rCounter] = returnstruct;
		rCounter++;
		return returnstruct;
	}
	else if (one[0] == 'r' && two[0] != 'r')
	{

		if (two.length() == 1)
			two += "Not";
		else
			two = two[0];
		for (int i = 0; i < 100; i++)
		{
			if (rr[i].name == one)
			{
				current = rr[i];
				i = 100;
			}
		}
		cmos[counter].Mname = "MQ";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = current.head;
		cmos[counter].B = current.head;
		cmos[counter].G = two;
		cmos[counter].D = current.tail;
		cmos[counter].Type = "PMOS";
		returnstruct.head = current.head;
		returnstruct.tail = current.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		counter++;
		return returnstruct;
	}
	else if (one[0] != 'r' && two[0] == 'r')
	{
		if (one.length() == 1)
			one += "Not";
		else
			one = one[0];
		for (int i = 0; i < 100; i++)
		{
			if (rr[i].name == two)
			{
				current = rr[i];
				i = 100;
			}
		}
		cmos[counter].Mname = "MQ";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = current.head;
		cmos[counter].B = current.head;
		cmos[counter].G = one;
		cmos[counter].D = current.tail;
		cmos[counter].Type = "PMOS";
		returnstruct.head = current.head;
		returnstruct.tail = current.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		counter++;
		return returnstruct;
	}
}
R ANDn(string one, string two)
{
	R current;
	R current2;
	R returnstruct;
	if (one[0] != 'r' && two[0] != 'r')
	{
		if (one.length() == 2)
		{
			one = one.substr(0, 1);
			one += "Not";
		}
		if (two.length() == 2)
		{
			two = two.substr(0, 1);
			two += "Not";
		}
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].D = "W";
		cmos[counter].D += to_string(wirecount);
		wirecount++;
		cmos[counter].G = one;
		cmos[counter].Type = "NMOS";
		cmos[counter].S = "W";
		cmos[counter].S += to_string(wirecount);
		cmos[counter].B = cmos[counter].S;
		wirecount++;
		counter++;
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].D = cmos[counter - 1].S;
		cmos[counter].G = two;
		cmos[counter].Type = "NMOS";
		cmos[counter].S = "W";
		cmos[counter].S += to_string(wirecount);
		cmos[counter].B = cmos[counter].S;
		returnstruct.head = cmos[counter - 1].D;
		returnstruct.tail = cmos[counter].S;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		wirecount++;
		counter++;
		return returnstruct;
	}

	else if (one[0] == 'r' && two[0] != 'r')
	{
		if (two.length() == 2)
		{
			two = two.substr(0, 1);
			two += "Not";
		}
		current = findR(one);
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].D = current.tail;
		cmos[counter].G = two;
		cmos[counter].Type = "NMOS";
		cmos[counter].S = "W";
		cmos[counter].S += to_string(wirecount);
		cmos[counter].B = cmos[counter].S;
		returnstruct.head = current.head;
		returnstruct.tail = cmos[counter].S;
		wirecount++;
		counter++;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		return returnstruct;
	}
	else if (one[0] != 'r' && two[0] == 'r')
	{
		if (one.length() == 2)
		{
			one = one.substr(0, 1);
			one += "Not";
		}
		current = findR(two);
		// !r
		cmos[counter].Mname = "M";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].S = current.head;
		cmos[counter].B = cmos[counter].S;
		wirecount++;
		cmos[counter].G = one;
		cmos[counter].Type = "NMOS";
		cmos[counter].D = "W";
		cmos[counter].D += to_string(wirecount);
		returnstruct.tail = current.tail;
		returnstruct.head = cmos[counter].D;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		wirecount++;
		counter++;
		return returnstruct;

	}
	else if (one[0] == 'r' && two[0] == 'r')
	{
		current = findR(one);
		current2 = findR(two);
		returnstruct.head = current.head;
		returnstruct.tail = current2.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		replaceWires(current.tail, current2.head);
		rr[rCounter] = returnstruct;
		rCounter++;
		return returnstruct;
	}
}
R ORn(string one, string two)
{
	R current;
	R current2;
	R returnstruct;
	if (one[0] != 'r' && two[0] != 'r')
	{
		if (one.length() == 2)
		{
			one = one.substr(0, 1);
			one += "Not";
		}
		if (two.length() == 2)
		{
			two = two.substr(0, 1);
			two += "Not";
		}
		cmos[counter].Mname = "MQ";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].D = "W";
		cmos[counter].D += to_string(wirecount);
		cmos[counter].G = one;
		cmos[counter].S = "W";
		cmos[counter].S += to_string(1 + wirecount);
		cmos[counter].B = cmos[counter].S;
		cmos[counter].Type = "NMOS";

		cmos[counter + 1].Mname = "MQ";
		cmos[counter + 1].Mname += to_string(2 + counter);
		cmos[counter + 1].D = "W";
		cmos[counter + 1].D += to_string(wirecount);
		cmos[counter + 1].G = two;
		cmos[counter + 1].S = "W";
		cmos[counter + 1].S += to_string(wirecount + 1);
		cmos[counter + 1].B = cmos[counter + 1].S;
		cmos[counter + 1].Type = "NMOS";
		returnstruct.head = cmos[counter + 1].D;
		returnstruct.tail = cmos[counter + 1].S;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		wirecount += 2;
		counter += 2;
		return returnstruct;
	}
	else if (one[0] == 'r' && two[0] == 'r')
	{
		current = findR(one);
		current2 = findR(two);
		returnstruct.head = current.head;
		returnstruct.tail = current.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		replaceWires(current.tail, current2.tail);
		replaceWires(current.head, current2.head);
		rr[rCounter] = returnstruct;
		rCounter++;
		return returnstruct;
	}
	else if (one[0] == 'r' && two[0] != 'r')
	{
		if (two.length() == 2)
		{
			two = two.substr(0, 1);
			two += "Not";
		}
		current = findR(one);
		cmos[counter].Mname = "MQ";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].D = current.head;
		cmos[counter].G = two;
		cmos[counter].S = current.tail;
		cmos[counter].B = current.head;
		cmos[counter].Type = "NMOS";
		returnstruct.head = current.head;
		returnstruct.tail = current.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		counter++;
		return returnstruct;
	}
	else if (one[0] != 'r' && two[0] == 'r')
	{
		if (one.length() == 2)
		{
			one = one.substr(0, 1);
			one += "Not";
		}

		current = findR(two);
		cmos[counter].Mname = "MQ";
		cmos[counter].Mname += to_string(1 + counter);
		cmos[counter].D = current.head;
		cmos[counter].G = one;
		cmos[counter].S = current.tail;
		cmos[counter].B = current.head;
		cmos[counter].Type = "PMOS";
		returnstruct.head = current.head;
		returnstruct.tail = current.tail;
		returnstruct.name = "r";
		returnstruct.name += to_string(rCounter);
		rr[rCounter] = returnstruct;
		rCounter++;
		counter++;
		return returnstruct;
	}
}

bool isLetter(char x)
{
	if ((int(x) <= 90 && int(x) >= 65) || (int(x) <= 122 && int(x) >= 97))
		return true;
	else return false;
}

string bracketNots(int i)
{
	string finalExpCurrent;
label:
	if (exp1[i] == ')' && exp1[i + 1] != '\'') // Final Return
	{
		finalExpCurrent += ')';
		return finalExpCurrent;
	}
	else if (exp1[i] == ')' && exp1[i + 1] == '\'')
	{
		finalExpCurrent += ')';
		finalExpCurrent = removeNots(finalExpCurrent);
		return finalExpCurrent;
	}

	else if (exp1[i] == '(') {

		finalExpCurrent += '(';
		i++;
		stack<char> s3;
		s3.push('(');
		int ii = i;
		while (!s3.empty())
		{
			if (exp1[ii] == ')')
				s3.pop();
			else if (exp1[ii] == '(')
				s3.push('(');
			ii++;
		}
		finalExpCurrent += bracketNots(i);
		i = ii;
		if (exp1[i] == '\'')
			i++;
		goto label;
	}
	else
	{
		finalExpCurrent += exp1[i];
		i++;
		goto label;
	}
}
string removeNots(string exp)
{
	string andd = "&";
	string orr = "|";
	string returnstr = "";

	for (int i = 0; i < exp.length(); i++)
	{
		if (isLetter(exp[i]) && exp[i + 1] == '\'')
		{
			returnstr += exp[i];
			i++;
		}
		else if (isLetter(exp[i]) && exp[i + 1] != '\'')
		{
			returnstr += exp[i];
			returnstr += '\'';
		}

		else if (exp[i] == '|')
		{
			returnstr += '&';
		}
		else if (exp[i] == '&')
		{
			returnstr += '|';
		}
		else
		{
			returnstr += exp[i];
		}
	}
	return returnstr;
}
string remover()
{
	finalExp = "";
	if (exp1.find(")'") != string::npos)
	{
		while (exp1.find(")'") != string::npos)
		{
			int finder = 0;
			while (exp1[finder] != '(')
				finder++;
			int first = finder;
			stack<char> s;
			s.push(exp1[finder]);
			while (!s.empty())
			{
				finder++;
				if (exp1[finder] == ')')
					s.pop();
				else if (exp1[finder] == '(')
					s.push(exp1[finder]);
			}
			finder++;
			if (exp1[finder] == '\'')
				finder++;
			for (int index = 0; index < first; index++)
				finalExp += exp1[index];
			finalExp += '(';
			finalExp += bracketNots(first + 1);
			exp1 = exp1.substr(finder, exp1.length() - finder);
		}
		finalExp += exp1;
	}
	else
		finalExp = exp1;
	cout << finalExp << endl;
	return finalExp;
}
string priority(string exp)
{
	string a;
	stack<string> s1;
	for (int q = 0; q < exp.length(); q++)
	{
		if (isalpha(exp[q]) || exp[q] == '\'')
			a += exp[q];
		else if (exp[q] == '(')
		{
			s1.push("(");
		}
		else if (exp[q] == ')')
		{
			string letter;
			letter = s1.top();
			while (letter != "(")
			{
				a += letter;
				s1.pop();
				if (!s1.empty())
					letter = s1.top();
			}
			s1.pop();
		}
		else if (exp[q] == '&')
		{
			string letter;
			if (!s1.empty())
				letter = s1.top();
			while (letter != "(" && letter != "|" && !s1.empty())
			{
				a += letter;
				s1.pop();
				if (!s1.empty())
					letter = s1.top();
			}
			s1.push("&");
		}
		else if (exp[q] == '|')
		{
			string letter;
			if (!s1.empty())
				letter = s1.top();
			while (!s1.empty() && letter != "(")
			{
				a += letter;
				s1.pop();
				if (!s1.empty())
					letter = s1.top();
			}
			s1.push("|");
		}
	}
	while (!s1.empty())
	{
		a += s1.top();
		s1.pop();
	}
	return a;
}

void replaceWires(string a, string b)
{
	for (int i = 0; i < counter; i++)
	{
		if (cmos[i].B == b)
			cmos[i].B = a;
		if (cmos[i].D == b)
			cmos[i].D = a;
		if (cmos[i].G == b)
			cmos[i].G = a;
		if (cmos[i].S == b)
			cmos[i].S = a;

	}
}
void NOT(string exp)
{
	int y = stoi(exp);
	cmos[counter].Mname = "MQ";
	cmos[counter].Mname += to_string(1 + counter);
	cmos[counter].S = "VDD";
	cmos[counter].B = "VDD";
	cmos[counter].G = char(y);
	cmos[counter].Type = "PMOS";
	cmos[counter].D = char(y);
	cmos[counter].D += "Not";

	cmos[counter + 1].Mname = "MQ";
	cmos[counter + 1].Mname += to_string(2 + counter);
	cmos[counter + 1].S = "0";
	cmos[counter + 1].B = "0";
	cmos[counter + 1].G = char(y);
	cmos[counter + 1].Type = "NMOS";
	cmos[counter + 1].D = char(y);
	cmos[counter + 1].D += "Not";
	notcounter += 2;
}
void getNots(string exp)
{
	for (int i = 0; i < exp.length(); i++)
		if ((int(exp[i]) <= 90 && int(exp[i]) >= 65) || (int(exp[i]) <= 122 && int(exp[i]) >= 97))
			nots.insert(exp[i]);

	std::set<char>::iterator setIt = nots.begin();
	for (int i = 0; i < nots.size(); i++)
	{
		string x = to_string(*setIt);
		NOT(x);
		counter += 2;
		setIt++;
	}
}
string PUN(string postFix)
{
	stack<string> sPost;
	for (int i = 0; i < postFix.length(); i++)
	{
		if (isalpha(postFix[i]))
		{
			if (postFix[i + 1] == '\'')
			{
				sPost.push(postFix.substr(i, 2));
				i++;
			}
			else
				sPost.push(postFix.substr(i, 1));
		}
		else if (postFix[i] == '&')
		{
			string str1, str2;
			str1 = sPost.top();
			sPost.pop();

			str2 = sPost.top();
			sPost.pop();
			sPost.push(ANDp(str1, str2).name);

		}
		else if (postFix[i] == '|')
		{
			string str1, str2;
			str1 = sPost.top();
			sPost.pop();

			str2 = sPost.top();
			sPost.pop();
			sPost.push(ORp(str1, str2).name);

		}
	}
	return(sPost.top());
}
string PDN(string postFix)
{
	stack<string> sPost;
	for (int i = 0; i < postFix.length(); i++)
	{
		if (isalpha(postFix[i]))
		{
			if (postFix[i + 1] == '\'')
			{
				sPost.push(postFix.substr(i, 2));
				i++;
			}
			else
				sPost.push(postFix.substr(i, 1));
		}
		else if (postFix[i] == '&')
		{
			string str1, str2;
			str1 = sPost.top();
			sPost.pop();

			str2 = sPost.top();
			sPost.pop();
			sPost.push(ANDn(str1, str2).name);

		}
		else if (postFix[i] == '|')
		{
			string str1, str2;
			str1 = sPost.top();
			sPost.pop();

			str2 = sPost.top();
			sPost.pop();
			sPost.push(ORn(str1, str2).name);

		}
	}
	return(sPost.top());
}
void print()
{
	for (int i = 0; i < counter; i++)
	{
		if (i == notcounter)
			cout << endl;
		cout << cmos[i].Mname << " " << cmos[i].D << " " << cmos[i].G << " " << cmos[i].S << " "
			<< cmos[i].B << " " << cmos[i].Type << "\n";
	}
}
void circ()
{
	string instr;
	string out;
	getline(cin, instr);
	getNots(instr);
	int semi = 0;
	for (int i = 0; i < instr.length(); i++)
		if (instr[i] == ';')
			semi++;
	for (int i = 0; i < semi; i++)
	{
		out = instr.substr(0, 1);
		exp1 = instr.substr(2, instr.find(";") - 2);
		instr = instr.substr(instr.find(";") + 1);
		while (!isalpha(instr[0]))
			instr = instr.substr(1);
		string copy = exp1;
		cout << "PUN of " << out << ": ";
		string lastR = PUN(priority(remover()));
		replaceWires("VDD", findR(lastR).head);
		replaceWires(out, findR(lastR).tail);
		exp1 = removeNots(copy);
		cout << "PDN of " << out << ": ";
		lastR = PDN(priority(remover()));
		replaceWires(out, findR(lastR).head);
		replaceWires("0", findR(lastR).tail);
	}

	out = instr.substr(0, 1);
	exp1 = instr.substr(2);
	string copy = exp1;
	cout << "PUN of " << out << ": ";
	string lastR = PUN(priority(remover()));
	replaceWires("VDD", findR(lastR).head);
	replaceWires(out, findR(lastR).tail);
	exp1 = removeNots(copy);
	cout << "PDN of " << out << ": ";
	lastR = PDN(priority(remover()));
	replaceWires(out, findR(lastR).head);
	replaceWires("0", findR(lastR).tail);
	print();

}

int main()
{
	circ();
	system("pause");
	return 0;
}
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <map>

using namespace std;

extern char token[100000];
extern int num;   //��¼���γ���
extern char con_ch;  //��¼�ַ��ͳ���
extern char s[100000];  //��¼�ַ�������
extern enum typeId symbol;

extern ofstream outputfile;
extern ofstream errorfile;

extern int oldIndex;    //�������ָ�
extern int line;  //�к�
extern int debug;
extern int nameId;
extern bool error;

map<string, symbolItem> globalSymbolTable;
map<string, symbolItem> localSymbolTable;
map<string, map<string, symbolItem>> allLocalSymbolTable;  //�������еľֲ����ű� ���ڱ��������ĵ�ַ
vector<string> stringList;  //�������е��ַ���
vector<midCode> midCodeTable;
map<string, vector<midCode> > funcMidCodeTable;  //ÿ�������������м����
map<string, bool> funcInlineAble;  //�����Ƿ��������
vector<string> funcNameList;  //��������

int curFuncReturnType = -1;
string curFunctionName = "";
int realReturnType = -1;
int globalAddr = 0;
int localAddr = 0;
bool isMain = false;

//���ַ�����   ::=  "��ʮ���Ʊ���Ϊ32,33,35-126��ASCII�ַ���"
bool strings() {
	if (symbol == STRCON) {
		doOutput();
		outputfile << "<�ַ���>" << endl;
		getsym();  //Ԥ��һ�� ������ɶ
		return true;
	}
	else {
		return false;
	}
}

//������  ::= �ۣ�����˵�����ݣۣ�����˵������{���з���ֵ�������壾|���޷���ֵ�������壾}����������
bool procedure() {
	//���Ե��ó���˵�� ��Ϊ��[] �ǿ���û�е� ���Լ��㷵��falseҲ����˵�������ʧ��,���������Ҫ����
	constDeclaration(true);
	//���Ե��ñ���˵��
	variableDeclaration(true);
	while (true) {
		if (symbol == INTTK || symbol == CHARTK) {
			if (!haveReturnValueFunction()) {//���Ե����з���ֵ����
				return false;
			}
		}
		else if (symbol == VOIDTK) {
			if (!noReturnValueFunction()) { //���Ե����޷���ֵ����
				break;
			}
		}
		else {
			return false;
		}
	}
	//����������
	if (mainFunction()) {
		//��һ��������֮��ʣûʣ����  ������������ ��Ԥ��һ��
		checkBeforeFunc();
		if (isEOF()) {
			outputfile << "<����>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//������˵���� ::=  const���������壾;{ const���������壾;}
bool constDeclaration(bool isglobal) {
	if (symbol == CONSTTK) {
		doOutput();
		int re = getsym();  //����һ�� Ȼ����볣������
		if (re < 0) {  //û����һ�� ����
			return false;
		}
		else {
			if (!constDefinition(isglobal)) { //���ó�������
				return false;
			}  //����֮�� ��Ԥ��һ�� ����Ҫ�ٶ���
			else {
				if (isEOF()) {   //Ԥ�����˽�β
					return false;
				}
				if (symbol != SEMICN) {
					retractString(oldIndex);
					errorfile << line << " k\n";  //ȱ�ٷֺ�
					error = true;
					symbol = SEMICN;
				}
				if (symbol == SEMICN) {  //�ֺ�
					doOutput();
					//��ʼ����{ const���������壾;}
					while (true) {
						re = getsym();
						if (re < 0) {  //����ǿ���û�е�
							break;
						}
						if (symbol != CONSTTK) {  //����ǿ���û�е�
							break;
						}
						doOutput();
						//��ǰ��const �������¿�
						re = getsym();
						if (re < 0) {  //const ��ȱ�ٶ���
							return false;
						}
						if (!constDefinition(isglobal)) { //���ó�������
							return false;
						}
						if (isEOF()) {   //Ԥ�����˽�β
							return false;
						}
						//�������������� Ԥ����һ������
						if (symbol != SEMICN) {
							retractString(oldIndex);
							errorfile << line << " k\n";  //ȱ�ٷֺ�
							error = true;
							symbol = SEMICN;
						}
						doOutput();
					}
					outputfile << "<����˵��>" << endl;
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	else {
		return false;
	}
}

//���������壾 ::= int����ʶ��������������{,����ʶ��������������}
//                  | char����ʶ���������ַ���{,����ʶ���������ַ���}
bool constDefinition(bool isglobal) {
	string name;
	if (symbol == INTTK) {
		doOutput();
		int re = getsym();  //����һ�� Ȼ������ʶ��
		if (re < 0) {  //û����һ�� ����
			return false;
		}
		else {
			if (symbol == IDENFR) {  //������ʶ��
				name = string(token);
				doOutput();
				re = getsym();  //����һ�� ����=
				if (re < 0) {
					return false;
				}
				else {
					if (symbol == ASSIGN) {  //����=
						doOutput();
						re = getsym();  //�ٶ�һ�� ��������
						if (re < 0) {
							return false;
						}
						else {
							int conInt;
							if (integer(conInt)) {  //����  Ԥ������һ������
								//��ʼ����{,����ʶ��������������}����
								if (isglobal) {
									if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
										globalSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 1, conInt)));
									}
									else {  //�ҵ��� ˵���ض�����
										errorfile << line << " b\n";
										error = true;
									}
								}
								else {
									if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
										localSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 1, conInt)));
									}
									else {  //�ҵ��� ˵���ض�����
										errorfile << line << " b\n";
										error = true;
									}
								}
								//midCodeTable.push_back(midCode(CONST, "int", name, int2string(conInt)));
							}
							else {  //��������ʧ�� û��Ԥ�� ��Ҫ��һ��
								errorfile << line << " o\n";
								error = true;
								getsym();
							}
							while (true) {
								if (isEOF()) {  //Ԥ�����˽�β
									break;
								}
								if (symbol != COMMA) {  //����ǿ���û�е�
									break;
								}
								doOutput();
								//��ǰ��,���� �������¿�
								re = getsym();
								if (re < 0) {  //, ��ȱ�ٶ���
									return false;
								}
								if (symbol != IDENFR) { //,���Ǳ�ʶ��
									return false;
								}
								doOutput();
								name = string(token);
								//��ǰ�Ǳ�ʶ��
								re = getsym();
								if (re < 0) {  //��ʶ����ȱ�ٶ���
									return false;
								}
								if (symbol != ASSIGN) { //��ʶ������=
									return false;
								}
								doOutput();
								//��ǰ��=
								re = getsym();
								if (re < 0) {  //=��ȱ�ٶ���
									return false;
								}
								if (integer(conInt)) {
									if (isglobal) {
										if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
											globalSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 1, conInt)));
										}
										else {  //�ҵ��� ˵���ض�����
											errorfile << line << " b\n";
											error = true;
										}
									}
									else {
										if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
											localSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 1, conInt)));
										}
										else {  //�ҵ��� ˵���ض�����
											errorfile << line << " b\n";
											error = true;
										}
									}
									//midCodeTable.push_back(midCode(CONST, "int", name, int2string(conInt)));
								}
								else {  //��������ʧ�� û��Ԥ�� ��Ҫ��һ��
									errorfile << line << " o\n";
									error = true;
									getsym();
								}
							}
							outputfile << "<��������>" << endl;
							return true;
						}
					}
					else {
						return false;
					}
				}
			}
			else {  //���Ǳ�ʶ��
				return false;
			}
		}
	}
	else if (symbol == CHARTK) {  //char����ʶ���������ַ���{,����ʶ���������ַ���}
		doOutput();
		int re = getsym();  //����һ�� Ȼ������ʶ��
		if (re < 0) {  //û����һ�� ����
			return false;
		}
		else {
			if (symbol == IDENFR) {  //������ʶ��
				doOutput();
				name = string(token);
				re = getsym();  //����һ�� ����=
				if (re < 0) {
					return false;
				}
				else {
					if (symbol == ASSIGN) {  //����=
						doOutput();
						re = getsym();  //�ٶ�һ�� �����ַ�
						if (re < 0) {
							return false;
						}
						else {
							if (symbol == CHARCON) {  //�ַ�����
								doOutput();
								if (isglobal) {
									if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
										globalSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 2, 0, con_ch)));
									}
									else {  //�ҵ��� ˵���ض�����
										errorfile << line << " b\n";
										error = true;
									}
								}
								else {
									if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
										localSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 2, 0, con_ch)));
									}
									else {  //�ҵ��� ˵���ض�����
										errorfile << line << " b\n";
										error = true;
									}
								}
								//midCodeTable.push_back(midCode(CONST, "char", name, int2string(con_ch)));
							}
							else {
								errorfile << line << " o\n";
								error = true;
							}
							//��ʼ����{,����ʶ���������ַ���}����
							while (true) {
								re = getsym();
								if (re < 0) {  //����ǿ���û�е�
									break;
								}
								if (symbol != COMMA) {  //����ǿ���û�е�
									break;
								}
								doOutput();
								//��ǰ��,���� �������¿�
								re = getsym();
								if (re < 0) {  //, ��ȱ�ٶ���
									return false;
								}
								if (symbol != IDENFR) { //,���Ǳ�ʶ��
									return false;
								}
								doOutput();
								name = string(token);
								//��ǰ�Ǳ�ʶ��
								re = getsym();
								if (re < 0) {  //��ʶ����ȱ�ٶ���
									return false;
								}
								if (symbol != ASSIGN) { //��ʶ������=
									return false;
								}
								doOutput();
								//��ǰ��=
								re = getsym();
								if (re < 0) {  //=��ȱ�ٶ���
									return false;
								}
								if (symbol == CHARCON) {
									doOutput();
									if (isglobal) {
										if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
											globalSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 2, 0, con_ch)));
										}
										else {  //�ҵ��� ˵���ض�����
											errorfile << line << " b\n";
											error = true;
										}
									}
									else {
										if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
											localSymbolTable.insert(make_pair(name, symbolItem(name, -1, 2, 2, 0, con_ch)));
										}
										else {  //�ҵ��� ˵���ض�����
											errorfile << line << " b\n";
											error = true;
										}
									}
									//midCodeTable.push_back(midCode(CONST, "char", name, int2string(con_ch)));
								}
								else {
									errorfile << line << " o\n";
									error = true;
								}
							}
							outputfile << "<��������>" << endl;
							return true;
						}
					}
					else {
						return false;
					}
				}
			}
			else {  //���Ǳ�ʶ��
				return false;
			}
		}
	}
	else {
		return false;
	}
}

//���޷���������  ::= ���������֣��������֣���| 0
bool unsignedInteger(int& value) {
	if (symbol == INTCON) {
		doOutput();
		value = num;
		getsym();    //Ԥ��һ������ ���ܳɹ���� ���÷���true ��ΪԤ���ɹ����Ӱ��ԡ����������ж�
		outputfile << "<�޷�������>" << endl;
		return true;
	}
	else {
		return false;
	}
}

//�������� ::= �ۣ������ݣ��޷���������
bool integer(int& value) {
	int re;
	if (symbol == PLUS || symbol == MINU) {
		bool isPLUS = (symbol == PLUS);
		doOutput();
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (unsignedInteger(value)) {  //�����޷�������
			if (!isPLUS) {  //����
				value = -value;
			}
			outputfile << "<����>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (unsignedInteger(value)) {  //ֱ�ӵ����޷�������
			outputfile << "<����>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
}

//������ͷ����   ::=  int����ʶ���� |char����ʶ����
bool declarationHead(string& tmp, int& type) {
	if (symbol == INTTK || symbol == CHARTK) {
		if (symbol == INTTK) {
			type = 1;
		}
		else {
			type = 2;
		}
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != IDENFR) {
			return false;
		}
		//��ǰ�Ǳ�ʶ�� �ɹ���
		doOutput();
		tmp = string(token);
		outputfile << "<����ͷ��>" << endl;
		re = getsym();  //Ԥ�� ���ܶ���ʲô
		return true;
	}
	else {
		return false;
	}
}

//������˵����  ::= ���������壾;{���������壾;}
bool variableDeclaration(bool isglobal) {
	//����˵�� �������� �� �з���ֵ�ĺ�������ǰ׺�г�ͻ
	//����ֻ���ڣ�����::=�ۣ�����˵�����ݣۣ�����˵������{���з���ֵ�������壾|���޷���ֵ�������壾}����������
	//�ڳ�������ķ���������Ҫ������
	//�ڣ�������䣾  ::=  �ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�
	//�����������ķ��� ���߲������ͬʱ���� ���Կ�����������
	if (!isglobal) {  //��Ҫ�����ǲ����з���ֵ�ĺ�����
		if (symbol == INTTK || symbol == CHARTK) {
			if (!variableDefinition(isglobal)) {  //���ñ�������
				return false;
			}
			//��������ɹ� Ԥ����һ������
			if (isEOF()) {
				return false;
			}
			if (symbol != SEMICN) {
				retractString(oldIndex);
				errorfile << line << " k\n";  //ȱ�ٷֺ�
				error = true;
				symbol = SEMICN;
			}
			if (symbol == SEMICN) {  //�����ֺ�  ���������壾;�ⲿ�ֽ�����
				doOutput();
				//����������{���������壾;}
				while (true) {
					int re = getsym();
					if (re < 0) {
						break;
					}
					if (!variableDefinition(isglobal)) {  //���Ǳ������� ����break
						break;
					}
					//��ǰ�Ǳ������� �����Ѿ�Ԥ����
					if (isEOF()) {
						return false;
					}
					if (symbol != SEMICN) {
						retractString(oldIndex);
						errorfile << line << " k\n";  //ȱ�ٷֺ�
						error = true;
						symbol = SEMICN;
					}
					doOutput();
				}
				outputfile << "<����˵��>" << endl;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {  //��Ҫ���� �����Ǻ���  ���ֵ�λ���ڵ���λ ���� int a (  �� ���������� int a ,[;�����
		int old = oldIndex;   //��¼��ȡ��int/char֮�������Ǹ�oldIndex �������int/char����ʼλ��
		if (symbol == INTTK || symbol == CHARTK) {
			int re = getsym(0);  //����һ��
			if (re < 0) {
				return false;
			}
			else {  //������ Ӧ���Ǳ�ʶ���Ŷ�
				if (symbol == IDENFR) {
					re = getsym(0);  //����һ��
					if (re < 0) {
						return false;
					}
					else {  //ͨ������(���Ǳ������������
						if (symbol == LPARENT) {  //��( ˵�����Ӧ���Ǻ������� ���Ǳ�������  ��Ҫ��Ҫ�Ѷ���������˻�ȥ ���ش���
							retractString(old);   //ָ��ص�û�ж�ȡint/char֮ǰ��λ��
							getsym(0);  //��int/char������
							return false;
						}
						else {  //Ӧ�������������ñ��������� ע��Ҳ��Ҫ�Ѷ���������˻�ȥ
							retractString(old);   //ָ��ص�û�ж�ȡint/char֮ǰ��λ��
							getsym();  //��int/char������
							//��ʼ���ñ�������
							if (symbol == INTTK || symbol == CHARTK) {
								if (!variableDefinition(isglobal)) {  //���ñ�������
									return false;
								}
								//��������ɹ� Ԥ����һ������
								if (isEOF()) {
									return false;
								}
								if (symbol != SEMICN) {
									retractString(oldIndex);
									errorfile << line << " k\n";  //ȱ�ٷֺ�
									error = true;
									symbol = SEMICN;
								}
								if (symbol == SEMICN) {  //�����ֺ�  ���������壾;�ⲿ�ֽ�����
									doOutput();
									//����������{���������壾;}
									//ע������ڷ����� ���ܾ�����������  Ҳ����ÿһ�η��������������壾;����ʱ�� �����п����Ǻ���
									while (true) {
										re = getsym();
										if (re < 0) {
											break;
										}
										else {
											old = oldIndex;  //��¼��ȡ��int/char֮�������Ǹ�oldIndex �������int/char����ʼλ��
											if (symbol == INTTK || symbol == CHARTK) {  //�õ���int/char ˵���п����Ǳ���������
												re = getsym(0);  //����һ��
												if (re < 0) {
													return false;   //???
												}
												else {
													if (symbol == IDENFR) {  //�Ǳ�ʶ��
														re = getsym(0);  //����һ��
														if (re < 0) {
															return false;   //???
														}
														else {  //ͨ������(���Ǳ������������
															if (symbol == LPARENT) {  //��( ˵�����Ӧ���Ǻ������� ���Ǳ�������  ��Ҫ��Ҫ�Ѷ���������˻�ȥ break
																retractString(old);   //ָ��ص�û�ж�ȡint/char֮ǰ��λ��
																getsym(0);  //��int/char������
																break;
															}
															else {  //Ӧ�������������ñ��������� ע��Ҳ��Ҫ�Ѷ���������˻�ȥ
																retractString(old);   //ָ��ص�û�ж�ȡint/char֮ǰ��λ��
																getsym();  //��int/char������
																//��ʼ���ñ�������
																if (symbol == INTTK || symbol == CHARTK) {
																	if (!variableDefinition(isglobal)) {  //���ñ�������
																		break;
																	}
																	//��������ɹ� Ԥ����һ������
																	if (isEOF()) {
																		return false;
																	}
																	if (symbol != SEMICN) {
																		retractString(oldIndex); //����� �˻�ȥ
																		errorfile << line << " k\n";  //ȱ�ٷֺ�
																		error = true;
																		symbol = SEMICN;
																	}
																	if (symbol == SEMICN) {  //�����ֺ�  ���������壾;�ⲿ�ֽ�����
																		doOutput();
																	}
																	else {
																		return false;
																	}
																}
															}
														}
													}
													else {  //���Ǳ�ʶ��
														return false;
													}
												}
											}
											else {  //������ǵĻ� ˵�����˽�����
												break;
											}
										}
									}
									outputfile << "<����˵��>" << endl;
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
}
//���������壾  ::= �����ͱ�ʶ����(����ʶ����|����ʶ����'['���޷���������']')
//                              {,(����ʶ����|����ʶ����'['���޷���������']' )}
bool variableDefinition(bool isglobal) {
	string name;
	int type;
	if (symbol == INTTK || symbol == CHARTK) {
		if (symbol == INTTK) {
			type = 1;
		}
		else {
			type = 2;
		}
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		else {
			if (symbol == IDENFR) {   //��ʶ��
				doOutput();
				name = string(token);
				re = getsym();
				if (symbol == LBRACK) {  //[
					doOutput();
					re = getsym();  //Ԥ��һ�� Ȼ������б� �޷�������
					if (re < 0) {
						return false;
					}
					else {
						int conInt;
						if (!unsignedInteger(conInt)) {  //�����޷�������
							return false;
						}
						//��ǰ���޷������� �Ѿ�Ԥ������һ�� �ж��ǲ���]
						if (symbol != RBRACK) {
							retractString(oldIndex);
							errorfile << line << " m\n";  //ȱ����������
							error = true;
							symbol = RBRACK;
						}
						if (symbol != RBRACK) {
							return false;
						}
						else {  // ]
							doOutput();
							if (isglobal) {
								if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
									globalSymbolTable.insert(make_pair(name, symbolItem(name, globalAddr, 4, type, 0, ' ', conInt)));
									globalAddr += conInt;
								}
								else {  //�ҵ��� ˵���ض�����
									errorfile << line << " b\n";
									error = true;
								}
							}
							else {
								if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
									localSymbolTable.insert(make_pair(name, symbolItem(name, localAddr, 4, type, 0, ' ', conInt)));
									localAddr += conInt;
								}
								else {  //�ҵ��� ˵���ض�����
									errorfile << line << " b\n";
									error = true;
								}
							}
							re = getsym();  //���һ�� ������ɶ ��Ϊ���û��[��ʱ�� Ҳ�Ѿ�Ԥ����һ��
							//midCodeTable.push_back(midCode(ARRAY, type==1 ? "int" : "char", name, int2string(conInt)));
						}
					}
				}  //�������[ ���൱��Ԥ����
				else {
					if (isglobal) {
						if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
							globalSymbolTable.insert(make_pair(name, symbolItem(name, globalAddr, 1, type)));
							globalAddr++;
						}
						else {  //�ҵ��� ˵���ض�����
							errorfile << line << " b\n";
							error = true;
						}
					}
					else {
						if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
							localSymbolTable.insert(make_pair(name, symbolItem(name, localAddr, 1, type)));
							localAddr++;
						}
						else {  //�ҵ��� ˵���ض�����
							errorfile << line << " b\n";
							error = true;
						}
					}
					//midCodeTable.push_back(midCode(VAR, type == 1 ? "int" : "char", name, ""));
				}
				//����[ ����[]������ ���������� {,(����ʶ����|����ʶ����'['���޷���������']' )}
				//���в�ͬ ��Ϊ��һ���Ѿ�����һ������ ����ѭ����Ҫ���̶�����
				while (true) {
					if (symbol != COMMA) {  //���� ,  ˵��û���ⲿ������
						break;
					}
					doOutput();
					//��ǰ��, �ж���һ���ǲ��Ǳ�ʶ��
					re = getsym();
					if (re < 0) {
						return false;
					}
					else {
						if (symbol == IDENFR) {   //��ʶ��
							doOutput();
							name = string(token);
							re = getsym();
							if (symbol == LBRACK) {  //[
								doOutput();
								re = getsym();  //Ԥ��һ�� Ȼ������б� �޷�������
								if (re < 0) {
									return false;
								}
								else {
									int conInt;
									if (!unsignedInteger(conInt)) {  //�����޷�������
										return false;
									}
									//��ǰ���޷������� �Ѿ�Ԥ������һ�� �ж��ǲ���]
									if (symbol != RBRACK) {
										retractString(oldIndex);
										errorfile << line << " m\n";  //ȱ����������
										error = true;
										symbol = RBRACK;
									}
									if (symbol != RBRACK) {
										return false;
									}
									else {  // ]
										doOutput();
										if (isglobal) {
											if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
												globalSymbolTable.insert(make_pair(name, symbolItem(name, globalAddr, 4, type, 0, ' ', conInt)));
												globalAddr += conInt;
											}
											else {  //�ҵ��� ˵���ض�����
												errorfile << line << " b\n";
												error = true;
											}
										}
										else {
											if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
												localSymbolTable.insert(make_pair(name, symbolItem(name, localAddr, 4, type, 0, ' ', conInt)));
												localAddr += conInt;
											}
											else {  //�ҵ��� ˵���ض�����
												errorfile << line << " b\n";
												error = true;
											}
										}
										re = getsym();  //���һ�� ������ɶ ��Ϊ���û��[��ʱ�� Ҳ�Ѿ�Ԥ����һ��
										//midCodeTable.push_back(midCode(ARRAY, type == 1 ? "int" : "char", name, int2string(conInt)));
									}
								}
							}  //�������[ ���൱��Ԥ����
							else {
								if (isglobal) {
									if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
										globalSymbolTable.insert(make_pair(name, symbolItem(name, globalAddr, 1, type)));
										globalAddr++;
									}
									else {  //�ҵ��� ˵���ض�����
										errorfile << line << " b\n";
										error = true;
									}
								}
								else {
									if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
										localSymbolTable.insert(make_pair(name, symbolItem(name, localAddr, 1, type)));
										localAddr++;
									}
									else {  //�ҵ��� ˵���ض�����
										errorfile << line << " b\n";
										error = true;
									}
								}
								//midCodeTable.push_back(midCode(VAR, type == 1 ? "int" : "char", name, ""));
							}
						}
						else {
							return false;
						}
					}
				}
				outputfile << "<��������>" << endl;
				return true;
				//}
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

void checkBeforeFunc() {
	int i;
	for (i = midCodeTable.size() - 1; i >= 0; i--) {
		if (midCodeTable[i].op == FUNC) {  //��ǰ�Һ�������
			break;
		}
	}
	if (i == -1) {  //û��break ��ζ��û���ҵ�ǰ�ߵ�FUNC
		return;
	}
	string funcName = midCodeTable[i].x;
	if (funcMidCodeTable.find(funcName) != funcMidCodeTable.end()) {
		return;
	}
	else {
		vector<midCode> ve = vector<midCode>();
		bool flag = true;
		//����+��ʱ����+�ֲ����� ��ȥ ��������
		int varCnt = globalSymbolTable[funcName].length - globalSymbolTable[funcName].parameterTable.size();
		if (debug) {
			cout << "varCnt0 = " << varCnt << "\n";
		}
		for (map<string, symbolItem>::iterator it = allLocalSymbolTable[funcName].begin();
										it != allLocalSymbolTable[funcName].end(); it++) { //��������ʱ����
			if ((*it).first[0] == '#') {
				varCnt--;
			}
		}
		if (varCnt > 2) {  //�ֲ���������2�� �Ͳ�������
			flag = false;
		}
		if (debug) {
			cout << "varCnt1 = " << varCnt << "\n";
		}
		//����ȫ�ֱ����Ĳ����� ȫ�ֳ������� ��Ϊ�����Ѿ���������������
		for (int j = i; j < midCodeTable.size(); j++) {
			midCode mc = midCodeTable[j];
			ve.push_back(mc);
			switch (mc.op) {
			case PLUSOP:
			case MINUOP:
			case MULTOP:
			case DIVOP:
				if (allLocalSymbolTable[funcName].find(mc.z) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.z) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				if (allLocalSymbolTable[funcName].find(mc.y) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.y) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				if (allLocalSymbolTable[funcName].find(mc.x) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.x) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				break;
			case LSSOP:
			case LEQOP:
			case GREOP:
			case GEQOP:
			case EQLOP:
			case NEQOP:
				if (allLocalSymbolTable[funcName].find(mc.y) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.y) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				if (allLocalSymbolTable[funcName].find(mc.x) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.x) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				break;
			case ASSIGNOP:
			case GETARRAY:  //mc.z << " = " << mc.x << "[" << mc.y << "]
				if (allLocalSymbolTable[funcName].find(mc.z) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.z) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				if (allLocalSymbolTable[funcName].find(mc.x) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.x) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				break;
			case GOTO:
			case BZ:
			case BNZ:
			case LABEL:
			case PUSH:
			case CALL:
			case RETVALUE:
				flag = false;
				break;
			case RET:
			case INLINERET:
			case SCAN:
				if (allLocalSymbolTable[funcName].find(mc.z) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.z) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				break;
			case PRINT:
				if (mc.x == "1" || mc.x == "2") {
					if (allLocalSymbolTable[funcName].find(mc.z) == allLocalSymbolTable[funcName].end() &&
						globalSymbolTable.find(mc.z) != globalSymbolTable.end()) {  //ȫ�ֱ���
						flag = false;
					}
				}
				break;
			case CONST:
			case ARRAY:
			case VAR:
			case PARAM:
				if (allLocalSymbolTable[funcName].find(mc.x) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.x) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				break;
			case PUTARRAY:  //mc.z << "[" << mc.x << "]" << " = " << mc.y
				if (allLocalSymbolTable[funcName].find(mc.z) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.z) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				if (allLocalSymbolTable[funcName].find(mc.y) == allLocalSymbolTable[funcName].end() &&
					globalSymbolTable.find(mc.y) != globalSymbolTable.end()) {  //ȫ�ֱ���
					flag = false;
				}
				break;
			case FUNC:
			case EXIT:
			default:
				break;
			}
		}
		funcMidCodeTable.insert(make_pair(funcName, ve));
		funcInlineAble.insert(make_pair(funcName, flag));
		return;
	}
}

//���з���ֵ�������壾  ::=  ������ͷ����'('��������')' '{'��������䣾'}��
bool haveReturnValueFunction() {
	string name;
	int type;
	if (!declarationHead(name, type)) {  //��������ͷ��
		return false;
	}
	curFunctionName = name;
	//��������ͷ���ɹ� Ԥ����һ������
	bool isRedefine = false;
	if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
		globalSymbolTable.insert(make_pair(name, symbolItem(name, -1, 3, type)));
		funcNameList.push_back(name);
		checkBeforeFunc();
		midCodeTable.push_back(midCode(FUNC, type == 1 ? "int" : "char", name, ""));
	}
	else {  //�ҵ��� ˵���ض�����
		errorfile << line << " b\n";
		error = true;
		isRedefine = true;
	}
	curFuncReturnType = type;
	if (isEOF()) {
		return false;
	}
	if (symbol == LPARENT) {  //����ͷ�������(
		doOutput();
		int re = getsym();  //Ϊ����������Ԥ��
		if (re < 0) {
			return false;
		}
		//��ʼ����������
		if (!parameterTable(name, isRedefine)) {
			return false;
		}
		//����������ɹ� Ԥ����һ������
		if (isEOF()) {
			return false;
		}
		if (symbol != RPARENT) {
			retractString(oldIndex);
			errorfile << line << " l\n";  //ȱ����С����
			error = true;
			symbol = RPARENT;
		}
		if (symbol == RPARENT) {  //����������)
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (symbol != LBRACE) {  //)��߲���{
				return false;
			}
			//��ǰ��{  Ϊ�����������Ԥ��
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			realReturnType = -1;  //��ʼ��һ����ʵ�ķ������� �����ж��Ƿ�������return���
			if (!compoundStatement()) {  //��ʼ�����������
				return false;
			}
			//�����������ɹ� Ԥ����һ������
			if (isEOF()) {
				return false;
			}
			if (symbol == RBRACE) {  //�����������}
				doOutput();
				if (realReturnType == -1) {  //û��������return���
					errorfile << line << " h\n";  //�з���ֵ�ĺ���ȱ��return���
					error = true;
				}
				outputfile << "<�з���ֵ��������>" << endl;
				re = getsym();  //Ԥ�� ���ܶ���ʲô
				if (debug) {
					showLocal();
				}
				allLocalSymbolTable.insert(make_pair(name, localSymbolTable));
				globalSymbolTable[name].length = localAddr;
				localSymbolTable.clear();
				localAddr = 0;
				curFuncReturnType = -1; //�Ѻ������ͻָ���-1
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//���޷���ֵ�������壾  ::= void����ʶ����'('��������')''{'��������䣾'}��
bool noReturnValueFunction() {
	//�޷���ֵ������main����ǰ׺�г�ͻ ��Ҫ���һ����Ԥ��
	string name;
	int old = oldIndex;   //��¼��ȡ��voidֻ�е�oldIndex ��void����ʼλ��
	if (symbol == VOIDTK) {
		//doOutput();
		int re = getsym(0);
		if (re < 0) {
			return false;
		}
		if (symbol != IDENFR && symbol != MAINTK) {  //���Ǳ�ʶ�� Ҳ���� main
			return false;
		}
		//doOutput();
		//��ǰ�Ǳ�ʶ�� ��Ҫ֪�������ʶ���ǲ���main
		if (symbol == MAINTK) {  //˵����main���� ��Ҫ�ָ���ȥ
			retractString(old);   //���˵�void����ʼλ��
			getsym(0);  //���¶�����void
			return false;
		}
		//˵�����޷���ֵ������ token��Ĳ���main
		symbol = VOIDTK;  //û���޸�token ���ֱ�ӻظ�symbol�Ϳ�����
		doOutput();
		symbol = IDENFR;
		doOutput();
		name = string(token);
		curFunctionName = name;
		bool isRedefine = false;
		if (globalSymbolTable.find(name) == globalSymbolTable.end()) {  //û�ҵ�
			globalSymbolTable.insert(make_pair(name, symbolItem(name, -1, 3, 3)));
			funcNameList.push_back(name);
			checkBeforeFunc();
			midCodeTable.push_back(midCode(FUNC, "void", name, ""));
		}
		else {  //�ҵ��� ˵���ض�����
			errorfile << line << " b\n";
			error = true;
			isRedefine = true;
		}
		curFuncReturnType = 3;  //void
		//��ǰ�Ǳ�ʶ�� ����һ���ǲ���(
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //��ʶ�������(
			doOutput();
			re = getsym();  //Ϊ����������Ԥ��
			if (re < 0) {
				return false;
			}
			//��ʼ����������
			if (!parameterTable(name, isRedefine)) {
				return false;
			}
			//����������ɹ� Ԥ����һ������
			if (isEOF()) {
				return false;
			}
			if (symbol != RPARENT) {
				retractString(oldIndex);
				errorfile << line << " l\n";  //ȱ����С����
				error = true;
				symbol = RPARENT;
			}
			if (symbol == RPARENT) {  //����������)
				doOutput();
				re = getsym();
				if (re < 0) {
					return false;
				}
				if (symbol != LBRACE) {  //)��߲���{
					return false;
				}
				//��ǰ��{  Ϊ�����������Ԥ��
				doOutput();
				re = getsym();
				if (re < 0) {
					return false;
				}
				realReturnType = -1;  //��ʼ��һ����ʵ�ķ������� �����ж��Ƿ�������return���
				if (!compoundStatement()) {  //��ʼ�����������
					return false;
				}
				//�����������ɹ� Ԥ����һ������
				if (isEOF()) {
					return false;
				}
				if (symbol == RBRACE) {  //�����������}
					doOutput();
					outputfile << "<�޷���ֵ��������>" << endl;
					re = getsym();  //Ԥ�� ���ܶ���ʲô
					if (debug) {
						showLocal();
					}
					allLocalSymbolTable.insert(make_pair(name, localSymbolTable));
					globalSymbolTable[name].length = localAddr;
					localSymbolTable.clear();
					localAddr = 0;
					curFuncReturnType = -1; //�Ѻ������ͻָ���-1
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//��������    ::=  �����ͱ�ʶ��������ʶ����{,�����ͱ�ʶ��������ʶ����}| ���գ�
bool parameterTable(string funcName, bool isRedefine) {
	//���������Ϊ��  ������Ϊ��ʱ ��ǰ�ַ�����)������
	string name;
	int type;
	if (symbol == RPARENT || symbol == LBRACE) {  //) {
		outputfile << "<������>" << endl;
		return true;
	}
	if (symbol == INTTK || symbol == CHARTK) {
		if (symbol == INTTK) {
			type = 1;
		}
		else {
			type = 2;
		}
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != IDENFR) {
			return false;
		}
		//��ǰ�Ǳ�ʶ��  ��ʼ����{,�����ͱ�ʶ��������ʶ����}
		name = string(token);
		if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
			localSymbolTable.insert(make_pair(name, symbolItem(name, localAddr, 1, type)));
			localAddr++;
			if (!isRedefine) {
				globalSymbolTable[funcName].insert(type);
			}
			midCodeTable.push_back(midCode(PARAM, type == 1 ? "int" : "char", name, ""));
		}
		else {  //�ҵ��� ˵���ض�����
			errorfile << line << " b\n";
			error = true;
		}
		doOutput();
		while (true) {
			re = getsym();
			if (re < 0) {
				break;
			}
			if (symbol != COMMA) {
				break;
			}
			//��ǰ��, ����һ���ǲ������ͱ�ʶ��
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (symbol != INTTK && symbol != CHARTK) {
				return false;
			}
			if (symbol == INTTK) {
				type = 1;
			}
			else {
				type = 2;
			}
			//��ǰ�����ͱ�ʶ�� ����һ���ǲ��Ǳ�ʶ��
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (symbol != IDENFR) {
				return false;
			}
			//��ǰ�Ǳ�ʶ��
			doOutput();
			name = string(token);
			if (localSymbolTable.find(name) == localSymbolTable.end()) {  //û�ҵ�
				localSymbolTable.insert(make_pair(name, symbolItem(name, localAddr, 1, type)));
				localAddr++;
				if (!isRedefine) {
					globalSymbolTable[funcName].insert(type);
				}
				midCodeTable.push_back(midCode(PARAM, type == 1 ? "int" : "char", name, ""));
			}
			else {  //�ҵ��� ˵���ض�����
				errorfile << line << " b\n";
				error = true;
			}
		}
		outputfile << "<������>" << endl;
		return true;
	}
	else {
		return false;
	}
}

//��������䣾  ::=  �ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�
bool compoundStatement() {
	//���Ե��ó���˵�� ��Ϊ��[] �ǿ���û�е� ���Լ��㷵��falseҲ����˵�������ʧ��,���������Ҫ����
	constDeclaration(false);
	//���Ե��ñ���˵��
	variableDeclaration(false);  //������� ˵��ֻ�����Ǳ���˵�������������з���ֵ�ĺ��� ����Ҫ�б���
	//���������
	if (statementList()) {
		outputfile << "<�������>" << endl;
		return true;
	}
	else {
		return false;
	}
}

//����������    ::= void main��(����)�� ��{����������䣾��}��
bool mainFunction() {
	if (symbol == VOIDTK) {
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == MAINTK) {  //void�����main
			//��ǰ��main ����һ���ǲ���(
			isMain = true;
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			curFunctionName = "main";
			globalSymbolTable.insert(make_pair("main", symbolItem("main", -1, 3, 3)));
			funcNameList.push_back("main");
			checkBeforeFunc();
			midCodeTable.push_back(midCode(FUNC, "void", "main", ""));
			if (symbol == LPARENT) {  //main�����(
				doOutput();
				re = getsym();  //����һ���ǲ���)
				if (re < 0) {
					return false;
				}
				if (symbol != RPARENT) {
					retractString(oldIndex);
					errorfile << line << " l\n";  //ȱ����С����
					error = true;
					symbol = RPARENT;
				}
				if (symbol == RPARENT) {  //(�����)
					doOutput();
					re = getsym();
					if (re < 0) {
						return false;
					}
					if (symbol == LBRACE) { //)�����{
						//��ǰ��{  Ϊ�����������Ԥ��
						doOutput();
						re = getsym();
						if (re < 0) {
							return false;
						}
						if (!compoundStatement()) {  //��ʼ�����������
							return false;
						}
						//�����������ɹ� Ԥ����һ������
						if (isEOF()) {
							return false;
						}
						if (symbol == RBRACE) {  //�����������}
							doOutput();
							outputfile << "<������>" << endl;
							re = getsym();  //Ԥ�� ���ܶ���ʲô
							if (debug) {
								showLocal();
							}
							allLocalSymbolTable.insert(make_pair("main", localSymbolTable));
							globalSymbolTable["main"].length = localAddr;
							localSymbolTable.clear();
							localAddr = 0;
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//�����ʽ��    ::= �ۣ������ݣ��{���ӷ�����������}  
bool expression(int& type, string& ansTmp) {
	bool first = false;
	int re;
	bool isPLUS;
	if (symbol == PLUS || symbol == MINU) {
		isPLUS = (symbol == PLUS);
		doOutput();
		re = getsym();
		if (re < 0) {
			return false;
		}
		first = true;
	}
	//������ķ���
	string op1, op2, res;
	if (!item(type, op1)) {
		return false;
	}
	if (first) {  //��һ��ǰ����������
		if (!isPLUS) {  //����
			if (isdigit(op1[0]) || op1[0] == '-' || op1[0] == '+') {  //op1�ǳ���
				int v1 = string2int(op1);
				op1 = int2string(-v1);
			}
			else {
				res = genTmp();
				localSymbolTable.insert(make_pair(res, symbolItem(res, localAddr, 1, 1)));  //kind=1=var,type=1=int
				localAddr++;
				midCodeTable.push_back(midCode(MINUOP, res, int2string(0), op1));
				op1 = res;
			}
		}
	}
	//������ɹ� ��Ԥ����һ������
	bool flag = false;
	//��ʼ����{���ӷ�����������} 
	while (true) {
		if (isEOF()) {
			break;
		}
		if (symbol != PLUS && symbol != MINU) {  //����+����-
			break;
		}
		//���а����˼ӷ����� ��һ����int��
		isPLUS = (symbol == PLUS);
		flag = true;
		doOutput();
		re = getsym();
		if (re < 0) {
			return false;
		}
		//������ķ���
		if (!item(type, op2)) {
			return false;
		}
		if ((isdigit(op1[0]) || op1[0] == '-' || op1[0] == '+') && (isdigit(op2[0]) || op2[0] == '-' || op2[0] == '+')) {
			int v1 = string2int(op1);
			int v2 = string2int(op2);
			if (isPLUS) {
				res = int2string(v1 + v2);
			}
			else {
				res = int2string(v1 - v2);
			}
		}
		else {
			res = genTmp();
			localSymbolTable.insert(make_pair(res, symbolItem(res, localAddr, 1, 1)));  //kind=1=var,type=1=int
			localAddr++;
			midCodeTable.push_back(midCode(isPLUS ? PLUSOP : MINUOP, res, op1, op2));
		}
		op1 = res;
	}
	if (first) {  //������ǰ�ߵ�+-�� һ����int
		type = 1;
	}
	else {
		if (flag) {  //���а����˼ӷ����� ��һ����int
			type = 1;
		}
	}
	ansTmp = op1;
	outputfile << "<���ʽ>" << endl;
	return true;
}

//���     ::= �����ӣ�{���˷�������������ӣ�}
bool item(int& type, string& ansTmp) {
	string op1, op2, res;
	if (!factor(type, op1)) {  //ֱ�ӷ�������
		return false;
	}
	//���ӷ����ɹ� ��Ԥ����һ������
	//��ʼ���� {���˷�������������ӣ�}
	bool flag = false;
	bool isMULT;
	while (true) {
		if (isEOF()) {
			break;
		}
		if (symbol != MULT && symbol != DIV) {  //����* Ҳ����/
			break;
		}
		isMULT = (symbol == MULT);
		doOutput();
		//���а����˳˷����� ��һ����int��
		flag = true;
		int re = getsym();
		if (re < 0) {
			return false;
		}
		//�������ӵķ���
		if (!factor(type, op2)) {
			return false;
		}
		if ((isdigit(op1[0]) || op1[0] == '-' || op1[0] == '+') && (isdigit(op2[0]) || op2[0] == '-' || op2[0] == '+')) {
			int v1 = string2int(op1);
			int v2 = string2int(op2);
			if (isMULT) {
				res = int2string(v1 * v2);
			}
			else {
				res = int2string(v1 / v2);
			}
		}
		else {
			res = genTmp();
			localSymbolTable.insert(make_pair(res, symbolItem(res, localAddr, 1, 1)));  //kind=1=var,type=1=int
			localAddr++;
			midCodeTable.push_back(midCode(isMULT ? MULTOP : DIVOP, res, op1, op2));
		}
		op1 = res;
	}
	if (flag) {  //���а����˳˷����� ��һ����int�� 
		type = 1;
	}
	ansTmp = op1;
	outputfile << "<��>" << endl;
	return true;
}

//�����ӣ�    ::= ����ʶ����������ʶ����'['�����ʽ��']'|'('�����ʽ��')'����������|���ַ��������з���ֵ����������䣾
//ע�� ���з���ֵ����������䣾 ::= ����ʶ����'('��ֵ������')���� ����ʶ����������ʶ����'['�����ʽ��']'|'('�����ʽ��')' ��ǰ׺�ĳ�ͻ
bool factor(int& type, string& ansTmp) {
	int re;
	int old = oldIndex;  //��¼��ȡ���ʶ��֮���oldIndex �Ǳ�ʶ������ʼλ��
	int conInt;
	if (symbol == IDENFR) {  //��ǰ�Ǳ�ʶ��  ��Ӧ�ķ� ����ʶ����������ʶ����'['�����ʽ��']' Ҳ������ ���з���ֵ����������䣾
		re = getsym(0);
		if (re < 0) {
			return false;
		}
		if (symbol == LBRACK) {  //��[
			symbol = IDENFR;
			string name = string(token);
			if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind == 4) { //��������kind=4
				type = localSymbolTable[name].type;
			}
			else {
				if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind == 4) { //��������kind=4
					type = globalSymbolTable[name].type;
				}
				else {
					errorfile << line << " c\n";  //δ���������
					error = true;
				}
			}
			doOutput();  //��Ϊ[�����޸�token ֻ��Ҫ��һ��symbol ��������ղŵı�ʶ����
			symbol = LBRACK;
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			//���뵽�Ա��ʽ�ķ���
			int t; 
			string op1;
			//����ʶ����'['�����ʽ��']'������ȡ���ڱ�ʶ�� �����Ǻ�ߵ������±� ���Բ�����type ����type���޸���
			if (!expression(t, op1)) {
				return false;
			}
			if (t != 1) {
				errorfile << line << " i\n";  //����Ԫ���±����Ͳ���int
				error = true;
			}
			//���ʽ�����ɹ� ��Ԥ����һ������
			if (symbol != RBRACK) {
				retractString(oldIndex);
				errorfile << line << " m\n";  //ȱ����������
				error = true;
				symbol = RBRACK;
			}
			if (symbol == RBRACK) {  //��]
				doOutput();
				re = getsym();   //Ϊ��һ��Ԥ�� ������ɶ
				string op2 = genTmp();
				localSymbolTable.insert(make_pair(op2, symbolItem(op2, localAddr, 1, type)));  //kind=1=var,type=�����type
				localAddr++;
				midCodeTable.push_back(midCode(GETARRAY, op2, name, op1));
				ansTmp = op2;
				outputfile << "<����>" << endl;
				return true;
			}
			else {
				return false;
			}
		}
		else if (symbol == LPARENT) {  //��( ˵������п�����  ���з���ֵ����������䣾  ��Ҫ�ָ�
			retractString(old);   //���˵���ʶ������ʼλ��
			getsym(0);   //�ѱ�ʶ�����¶�����
			//��ʼ���� �з���ֵ�ĺ����������
			string name = string(token);
			if (globalSymbolTable.find(name) != globalSymbolTable.end()
				&& globalSymbolTable[name].kind == 3
				&& (globalSymbolTable[name].type == 1 || globalSymbolTable[name].type == 2)
				&& localSymbolTable.find(name) == localSymbolTable.end()
				) {
				if (!callHaveReturnValueFunction()) {
					return false;
				}
				type = globalSymbolTable[name].type;
				string op1 = genTmp();
				localSymbolTable.insert(make_pair(op1, symbolItem(op1, localAddr, 1, type)));  //kind=1=var,type=������������
				localAddr++;
				//�����ǰ�м�������һ����INLINEEND ˵���˺���������
				if (midCodeTable[midCodeTable.size() - 1].op == INLINEEND) {
					if (midCodeTable[midCodeTable.size() - 2].op == INLINERET) {
						string value = midCodeTable[midCodeTable.size() - 2].z;
						midCodeTable[midCodeTable.size() - 2].op = ASSIGNOP;
						midCodeTable[midCodeTable.size() - 2].z = op1;
						midCodeTable[midCodeTable.size() - 2].x = value;
					}
				}
				else {
					midCodeTable.push_back(midCode(RETVALUE, op1, "RET", ""));
				}
				ansTmp = op1;
				//�����з���ֵ�ĺ����������ɹ� ��Ԥ����һ������
				outputfile << "<����>" << endl;
				return true;
			}
			else {
				errorfile << line << " c\n";  //δ���������
				error = true;
				while (1) {
					get_ch();
					if (isRparent()) {  //)  ��Ϊ���ӳ��ֵ� ����һֱ����;�� )�͵�ͣ
						break;
					}
				}
				outputfile << "<����>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
		}
		else {  //��ʶ����߲���[ Ҳ����(  ��Ӧ�ķ�����ʶ����  ֱ�ӷ��� ������ʾ���Ϊ��һ��Ԥ���ĵ�����
			//�������ֱ�ӷ��� ��ô�����ʶ����û���������
			retractString(old);   //���˵���ʶ������ʼλ��
			getsym(0);   //�ѱ�ʶ�����¶�����
			string name = string(token);
			bool isConstValue = false;
			int value;
			if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
				type = localSymbolTable[name].type;
				if (localSymbolTable[name].kind == 2) {
					isConstValue = true;
					if (type == 1) {
						value = localSymbolTable[name].constInt;
					}
					else {
						value = localSymbolTable[name].constChar;
					}
				}
			}
			else {
				if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
					type = globalSymbolTable[name].type;
					if (globalSymbolTable[name].kind == 2) {
						isConstValue = true;
						if (type == 1) {
							value = globalSymbolTable[name].constInt;
						}
						else {
							value = globalSymbolTable[name].constChar;
						}
					}
				}
				else {
					errorfile << line << " c\n";  //δ���������
					error = true;
				}
			}
			doOutput();
			if (isConstValue) {  //�����Ļ�ֱ�ӷ���ֵ
				ansTmp = int2string(value);
			}
			else {
				ansTmp = name;  //ֱ�ӷ���token
			}
			outputfile << "<����>" << endl;
			getsym();  //Ԥ��һ��
			return true;
		}
	}
	else if (symbol == LPARENT) {  //��ǰ��(  ��Ӧ�ķ� '('�����ʽ��')'
		doOutput();
		re = getsym();
		if (re < 0) {
			return false;
		}
		//���뵽�Ա��ʽ�ķ���
		if (!expression(type, ansTmp)) {
			return false;
		}
		type = 1;  //(���ʽ)��������;���int
		//���ʽ�����ɹ� ��Ԥ����һ������
		if (symbol != RPARENT) {
			retractString(oldIndex);
			errorfile << line << " l\n";  //ȱ����С����
			error = true;
			symbol = RPARENT;
		}
		if (symbol == RPARENT) {  //��)
			doOutput();
			re = getsym();   //Ϊ��һ��Ԥ�� ������ɶ
			outputfile << "<����>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (symbol == CHARCON) {  //��ǰ���ַ� ��Ӧ�ķ� ���ַ���
		type = 2;  //�ַ�����������char 
		doOutput();
		re = getsym();   //Ϊ��һ��Ԥ�� ������ɶ
		ansTmp = int2string(con_ch);
		outputfile << "<����>" << endl;
		return true;
	}
	else if (integer(conInt)) {  //��ǰ������   ��Ԥ����һ������
		type = 1;  //���γ��� ������int
		ansTmp = int2string(conInt);   //???�᲻��integer��Ԥ�� ������������
		outputfile << "<����>" << endl;
		return true;
	}
	else {
		type = 0;
		return false;
	}
}

//����䣾    ::= ��������䣾����ѭ����䣾| '{'������У�'}'| ���з���ֵ����������䣾; 
//              |���޷���ֵ����������䣾;������ֵ��䣾;��������䣾;����д��䣾;�����գ�;|��������䣾;
bool statement() {
	if (symbol == SEMICN) {  //;�ֺ�  һ���ֺ�ֱ�Ӿ���һ�����
		doOutput();
		outputfile << "<���>" << endl;
		getsym();  //Ԥ��һ�� ������ɶ
		return true;
	}
	else if (symbol == RETURNTK) {  //��������䣾;
		if (returnStatement()) {
			//�����������ɹ� ��Ԥ����һ������
			if (symbol != SEMICN) {
				retractString(oldIndex);
				errorfile << line << " k\n";  //ȱ�ٷֺ�
				error = true;
				symbol = SEMICN;
			}
			if (symbol == SEMICN) {  //;�ֺ�
				doOutput();
				outputfile << "<���>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (symbol == SCANFTK) {  //������䣾;
		if (readStatement()) {
			//���������ɹ� ��Ԥ����һ������
			if (symbol != SEMICN) {
				retractString(oldIndex);
				errorfile << line << " k\n";  //ȱ�ٷֺ�
				error = true;
				symbol = SEMICN;
			}
			if (symbol == SEMICN) {  //;�ֺ�
				doOutput();
				outputfile << "<���>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (symbol == PRINTFTK) {  //��д��䣾;
		if (writeStatement()) {
			//����д���ɹ� ��Ԥ����һ������
			if (symbol != SEMICN) {
				retractString(oldIndex);
				errorfile << line << " k\n";  //ȱ�ٷֺ�
				error = true;
				symbol = SEMICN;
			}
			if (symbol == SEMICN) {  //;�ֺ�
				doOutput();
				outputfile << "<���>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (symbol == IFTK) {  //��������䣾
		if (conditionStatement()) {
			//�����������ɹ� ��Ԥ����һ������
			outputfile << "<���>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (symbol == WHILETK || symbol == DOTK || symbol == FORTK) {  //��ѭ����䣾
		if (repeatStatement()) {
			//����ѭ�����ɹ� ��Ԥ����һ������
			outputfile << "<���>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else if (symbol == LBRACE) {  //'{'������У�'}'
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (!statementList()) {  //���������
			return false;
		}
		//��������� ��Ԥ����һ������
		if (symbol == RBRACE) {  //}
			doOutput();
			outputfile << "<���>" << endl;
			getsym();  //Ԥ��һ�� ������ɶ
			return true;
		}
		else {
			return false;
		}
	}
	else if (symbol == IDENFR) {  //���з���ֵ����������䣾; |���޷���ֵ����������䣾;������ֵ��䣾;
		int old = oldIndex;  //��¼�¶�ȡ���ʶ��֮���oldIndex ���������ʶ������ʼλ��
		int re = getsym(0);
		if (re < 0) {
			return false;
		}
		if (symbol == LBRACK || symbol == ASSIGN) {  //[ = ˵���Ǹ�ֵ���
			retractString(old);
			getsym(0);
			if (!assignStatement()) {
				return false;
			}
			//������ֵ���ɹ� ��Ԥ����һ������
			if (symbol != SEMICN) {
				retractString(oldIndex);
				errorfile << line << " k\n";  //ȱ�ٷֺ�
				error = true;
				symbol = SEMICN;
			}
			if (symbol == SEMICN) {  //;�ֺ�
				doOutput();
				outputfile << "<���>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else if (symbol == LPARENT) {  //( ˵���Ǻ����������
			retractString(old);
			getsym(0);
			string name = string(token);
			if (globalSymbolTable.find(name) != globalSymbolTable.end()
				&& globalSymbolTable[name].kind == 3
				&& localSymbolTable.find(name) == localSymbolTable.end()
				) {
				if (globalSymbolTable[name].type == 3) {  //func void
					if (!callNoReturnValueFunction()) {
						return false;
					}
					//�����޷���ֵ�����������ɹ� ��Ԥ����һ������
					if (symbol != SEMICN) {
						retractString(oldIndex);
						errorfile << line << " k\n";  //ȱ�ٷֺ�
						error = true;
						symbol = SEMICN;
					}
					if (symbol == SEMICN) {  //;�ֺ�
						doOutput();
						outputfile << "<���>" << endl;
						getsym();  //Ԥ��һ�� ������ɶ
						return true;
					}
					else {
						return false;
					}
				}
				else {  //func int char
					if (!callHaveReturnValueFunction()) {
						return false;
					}
					//�����з���ֵ�����������ɹ� ��Ԥ����һ������
					if (symbol != SEMICN) {
						retractString(oldIndex);
						errorfile << line << " k\n";  //ȱ�ٷֺ�
						error = true;
						symbol = SEMICN;
					}
					if (symbol == SEMICN) {  //;�ֺ�
						doOutput();
						outputfile << "<���>" << endl;
						getsym();  //Ԥ��һ�� ������ɶ
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {
				errorfile << line << " c\n";  //δ���������
				error = true;
				while (1) {
					get_ch();
					if (isSemicn()) {  //;
						break;
					}
				}
				outputfile << "<���>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
		}
		else {
			return false;
		}
	}
	else if (symbol == ELSETK || symbol == RBRACE) {
		errorfile << line << " k\n";
		error = true;
		return true;
	}
	else {
		return false;
	}
}

//����ֵ��䣾   ::=  ����ʶ�����������ʽ��|����ʶ����'['�����ʽ��']'=�����ʽ��
bool assignStatement() {
	string value;
	if (symbol == IDENFR) {  //�Ǳ�ʶ��
		string name = string(token);
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LBRACK) {  //[   ��Ӧ�ķ�����ʶ����'['�����ʽ��']'=�����ʽ��
			if (!((localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind == 4)  //����kind=4
				|| (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind == 4))
				) {
				errorfile << line << " c\n";  //δ���������
				error = true;
			}
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			//��ʼ�������ʽ
			int t;
			string op1;
			if (!expression(t, op1)) {  //t�������±������
				return false;
			}
			if (t != 1) {
				errorfile << line << " i\n";  //����Ԫ���±����Ͳ���int
				error = true;
			}
			//�������ʽ�ɹ� ��Ԥ����һ������
			if (symbol != RBRACK) {
				retractString(oldIndex);
				errorfile << line << " m\n";  //ȱ����������
				error = true;
				symbol = RBRACK;
			}
			if (symbol == RBRACK) {  //]
				doOutput();
				re = getsym();
				if (re < 0) {
					return false;
				}
				if (symbol == ASSIGN) {  // =
					doOutput();
					re = getsym();
					if (re < 0) {
						return false;
					}
					//��ʼ�������ʽ
					int tt;
					if (!expression(tt, value)) {
						return false;
					}
					//�������ʽ�ɹ� ��Ԥ����һ������
					midCodeTable.push_back(midCode(PUTARRAY, name, op1, value));
					outputfile << "<��ֵ���>" << endl;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else  if (symbol == ASSIGN) {  //= ��Ӧ�ķ� ����ʶ�����������ʽ��
			if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
				if (localSymbolTable[name].kind == 2) {  //const
					errorfile << line << " j\n";  //�ı䳣����ֵ��
					error = true;
				}
			}
			else {
				if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
					if (globalSymbolTable[name].kind == 2) {  //const
						errorfile << line << " j\n";  //�ı䳣����ֵ��
						error = true;
					}
				}
				else {
					errorfile << line << " c\n";  //δ���������
					error = true;
				}
			}
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			//��ʼ�������ʽ
			int t;
			if (!expression(t, value)) {
				return false;
			}
			if (value[0] == '#') {  //�м����
				int index = midCodeTable.size() - 1;
				if (midCodeTable.back().op == INLINEEND) {
					index--;
				}
				if (midCodeTable[index].z == value) {
					midCodeTable[index].z = name;
				}
				else {
					midCodeTable.push_back(midCode(ASSIGNOP, name, value, ""));
				}
			}
			else {
				midCodeTable.push_back(midCode(ASSIGNOP, name, value, ""));
			}
			//�������ʽ�ɹ� ��Ԥ����һ������
			outputfile << "<��ֵ���>" << endl;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//��������䣾  ::= if '('��������')'����䣾��else����䣾��
bool conditionStatement() {
	string laba, labb;
	if (symbol == IFTK) {  //if
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (!condition()) {  //��������
				return false;
			}
			//���������ɹ� ��Ԥ����һ������
			if (symbol != RPARENT) {
				retractString(oldIndex);
				errorfile << line << " l\n";  //ȱ����С����
				error = true;
				symbol = RPARENT;
			}
			if (symbol == RPARENT) {  //)
				doOutput();
				re = getsym();
				if (re < 0) {
					return false;
				}
				laba = genLabel();  //�������a
				midCodeTable.push_back(midCode(BZ, laba, "<>", ""));  //����������(result==0)����ת�����a
				string lbegin = genLabel("CB");
				midCodeTable.push_back(midCode(LABEL, lbegin, "", ""));  //if ��֧�Ŀ�ͷ
				if (!statement()) {  //�������
					return false;
				}
				//�������ɹ� ��Ԥ����һ������
				//��ʼ������else����䣾��
				if (symbol == ELSETK) {  //else
					doOutput();
					labb = genLabel();  //�������b
					midCodeTable.push_back(midCode(GOTO, labb, "", ""));  //��������ת�����b
					midCodeTable.push_back(midCode(LABEL, laba, "", ""));  //��else������ñ��a
					re = getsym();
					if (re < 0) {
						return false;
					}
					if (!statement()) {  //�������
						return false;
					}
					midCodeTable.push_back(midCode(LABEL, labb, "", ""));  //else���������ĺ�����ñ��b
					//�������ɹ� ��Ԥ����һ������
					//return true;
				} //����else ˵��û���ⲿ�� �ǿ��Ե�
				else {
					midCodeTable.push_back(midCode(LABEL, laba, "", ""));  //û��else ����������ñ��a
				}
				string lend = genLabel("CE");
				midCodeTable.push_back(midCode(LABEL, lend, "", ""));  //��������
				outputfile << "<�������>" << endl;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//��������  ::=  �����ʽ������ϵ������������ʽ���������ʽ��
bool condition() {
	int typeLeft, typeRight;
	string v1, v2;
	if (!expression(typeLeft, v1)) {  //ֱ�ӵ��ñ��ʽ
		return false;
	}
	//�������ʽ�ɹ� ��Ԥ��һ������
	if (symbol == LSS || symbol == LEQ || symbol == GRE || symbol == GEQ || symbol == EQL || symbol == NEQ) {  //��ϵ�����
		doOutput();
		operation op;
		switch (symbol) {
			case LSS:
				op = LSSOP; break;
			case LEQ:
				op = LEQOP; break;
			case GRE:
				op = GREOP; break;
			case GEQ:
				op = GEQOP; break;
			case EQL:
				op = EQLOP; break;
			case NEQ:
				op = NEQOP; break;
		}
		int re = getsym();
		if (re < 0) {
			return false;
		}
		//��ʼ�������ʽ
		if (!expression(typeRight, v2)) {
			return false;
		}
		//�������ʽ�ɹ� ��Ԥ����һ������
		if (typeLeft != 1 || typeRight != 1) {
			errorfile << line << " f\n";  //�����ж��г��ֲ��Ϸ������� Ҫ��ȫ��int����
			error = true;
		}
		midCodeTable.push_back(midCode(op, "<>", v1, v2));
		outputfile << "<����>" << endl;
		return true;
	}
	else {
		if (typeLeft != 1) {
			errorfile << line << " f\n";  //�����ж��г��ֲ��Ϸ������� Ҫ����int����
			error = true;
		}
		//ֻ��һ�����ʽ������ �൱�� ���ʽ!=0
		midCodeTable.push_back(midCode(NEQOP, "<>", v1, int2string(0)));
		outputfile << "<����>" << endl;
		return true;
	}
}

//��ѭ����䣾   ::=  while '('��������')'����䣾| do����䣾while '('��������')'
//              |for'('����ʶ�����������ʽ��;��������;����ʶ����������ʶ����(+|-)��������')'����䣾
bool repeatStatement() {
	if (symbol == WHILETK) {  //while '('��������')'����䣾
		doOutput();
		string labr, labf;
		labr = genLabel("LB");
		midCodeTable.push_back(midCode(LABEL, labr, "", ""));  //����labr ����ִ��һ��ѭ��֮��������
		int conditionBeginIndex = midCodeTable.size();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (!condition()) {  //��������
				return false;
			}
			//���������ɹ� ��Ԥ����һ������
			if (symbol != RPARENT) {
				retractString(oldIndex);
				errorfile << line << " l\n";  //ȱ����С����
				error = true;
				symbol = RPARENT;
			}
			if (symbol == RPARENT) {  //)
				doOutput();
				re = getsym();
				if (re < 0) {
					return false;
				}
				labf = genLabel("LE");
				midCodeTable.push_back(midCode(BZ, labf, "<>", ""));  //����������(result==0)�Ļ� ��ת��labf
				int conditionEndIndex = midCodeTable.size() - 1;
				string whileBody = genLabel("LO");
				midCodeTable.push_back(midCode(LABEL, whileBody, "", ""));
				if (!statement()) {  //�������
					return false;
				}
				//midCodeTable.push_back(midCode(GOTO, labr, "", ""));  //ִ����һ��ѭ���� �������ص�labr
				/*for (int ix = conditionBeginIndex; ix < conditionEndIndex; ix++) {
					midCode mc = midCodeTable[ix];
					midCodeTable.push_back(mc);
				}*/
				map<string, string> nMap;
				for (int ix = conditionBeginIndex; ix < conditionEndIndex; ix++) {
					midCode mc = midCodeTable[ix];
					if (mc.x[0] == '#' && nMap.find(mc.x) == nMap.end()) {
						nMap[mc.x] = genTmp();
					}
					if (mc.y[0] == '#' && nMap.find(mc.y) == nMap.end()) {
						nMap[mc.y] = genTmp();
					}
					if (mc.z[0] == '#' && nMap.find(mc.z) == nMap.end()) {
						nMap[mc.z] = genTmp();
					}
					if (mc.x[0] == '%' && nMap.find(mc.x) == nMap.end()) {
						nMap[mc.x] = genName();
					}
					if (mc.y[0] == '%' && nMap.find(mc.y) == nMap.end()) {
						nMap[mc.y] = genName();
					}
					if (mc.z[0] == '%' && nMap.find(mc.z) == nMap.end()) {
						nMap[mc.z] = genName();
					}
				}
				for (int ix = conditionBeginIndex; ix < conditionEndIndex; ix++) {
					midCode mc = midCodeTable[ix];
					if (mc.x[0] == '#' || mc.x[0] == '%') {
						mc.x = nMap[mc.x];
					}
					if (mc.y[0] == '#' || mc.y[0] == '%') {
						mc.y = nMap[mc.y];
					}
					if (mc.z[0] == '#' || mc.z[0] == '%') {
						mc.z = nMap[mc.z];
					}
					midCodeTable.push_back(mc);
				}
				for (map<string, string>::iterator it = nMap.begin(); it != nMap.end(); it++) {
					string oriName = (*it).first;
					string newName = (*it).second;
					symbolItem sitem = localSymbolTable[oriName];
					sitem.name = newName;
					sitem.addr = localAddr;
					localAddr++;
					localSymbolTable.insert(make_pair(newName, sitem));
				}
				midCodeTable.push_back(midCode(BNZ, whileBody, "<>", ""));  //�ص�whileBody
				midCodeTable.push_back(midCode(LABEL, labf, "", ""));  //����labf ���ڽ���ѭ��
				//�������ɹ� ��Ԥ����һ������
				outputfile << "<ѭ�����>" << endl;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (symbol == DOTK) {  // do����䣾while '('��������')'
		string labr = genLabel();
		midCodeTable.push_back(midCode(LABEL, labr, "", "")); //����labr ����ִ��һ��ѭ��֮�����
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (!statement()) {  //�������
			return false;
		}
		//�������ɹ� ��Ԥ����һ������
		if (symbol != WHILETK) {
			retractString(oldIndex);
			errorfile << line << " n\n";  //ȱ��while
			error = true;
			symbol = WHILETK;
		}
		if (symbol == WHILETK) {
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (symbol == LPARENT) {  //(
				doOutput();
				re = getsym();
				if (re < 0) {
					return false;
				}
				if (!condition()) {  //��������
					return false;
				}
				//���������ɹ� ��Ԥ����һ������
				if (symbol != RPARENT) {
					retractString(oldIndex);
					errorfile << line << " l\n";  //ȱ����С����
					error = true;
					symbol = RPARENT;
				}
				if (symbol == RPARENT) {  //)
					doOutput();
					midCodeTable.push_back(midCode(BNZ, labr, "<>", "")); //��������(result==1)�Ļ� ����labr ����ѭ��
					//string labf = genLabel("LE");
					//midCodeTable.push_back(midCode(LABEL, labf, "", ""));  //����labf ���ڽ���ѭ��
					outputfile << "<ѭ�����>" << endl;
					getsym(); //Ԥ��һ�� ������ɶ
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (symbol == FORTK) {  //for'('����ʶ�����������ʽ��;��������;����ʶ����������ʶ����(+|-)��������')'����䣾
		string lbegin, lend;
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != LPARENT) {  //(
			return false;
		}
		doOutput();  //��(
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != IDENFR) {  //���Ǳ�ʶ��
			return false;
		}
		doOutput();   //�Ǳ�ʶ��
		string name = string(token);
		if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
			if (localSymbolTable[name].kind == 2) {  //const
				errorfile << line << " j\n";  //�ı䳣����ֵ��
				error = true;
			}
		}
		else {
			if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
				if (globalSymbolTable[name].kind == 2) {  //const
					errorfile << line << " j\n";  //�ı䳣����ֵ��
					error = true;
				}
			}
			else {
				errorfile << line << " c\n";  //δ���������
				error = true;
			}
		}
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != ASSIGN) {  //����=
			return false;
		}
		doOutput();   //��=
		re = getsym();
		if (re < 0) {
			return false;
		}
		int t;
		string value;
		if (!expression(t, value)) {  //�������ʽ
			return false;
		}
		if (value[0] == '#') {  //�м����
			int index = midCodeTable.size() - 1;
			if (midCodeTable.back().op == INLINEEND) {
				index--;
			}
			if (midCodeTable[index].z == value) {
				midCodeTable[index].z = name;
			}
			else {
				midCodeTable.push_back(midCode(ASSIGNOP, name, value, ""));
			}
		}
		else {
			midCodeTable.push_back(midCode(ASSIGNOP, name, value, ""));
		}
		//�������ʽ�ɹ� ��Ԥ����һ������
		if (symbol != SEMICN) {
			retractString(oldIndex);
			errorfile << line << " k\n";  //ȱ�ٷֺ�
			error = true;
			symbol = SEMICN;
		}
		if (symbol == SEMICN) {  //;�ֺ�
			doOutput(); //��;
			re = getsym();
			if (re < 0) {
				return false;
			}
		}
		else {
			return false;
		}
		lbegin = genLabel("LB");
		midCodeTable.push_back(midCode(LABEL, lbegin, "", ""));  //������ǰ�߷�lbegin
		int conditionBeginIndex = midCodeTable.size();
		if (!condition()) {  //��������
			return false;
		}
		lend = genLabel("LE");
		midCodeTable.push_back(midCode(BZ, lend, "<>", "")); //����������(result==0)����lend ����for
		int conditionEndIndex = midCodeTable.size() - 1;
		string forBody = genLabel("LO");
		midCodeTable.push_back(midCode(LABEL, forBody, "", ""));
		//���������ɹ� ��Ԥ����һ������
		if (symbol != SEMICN) {
			retractString(oldIndex);
			errorfile << line << " k\n";  //ȱ�ٷֺ�
			error = true;
			symbol = SEMICN;
		}
		if (symbol == SEMICN) {  //;�ֺ�
			doOutput(); //��;
			re = getsym();
			if (re < 0) {
				return false;
			}
		}
		else {
			return false;
		}
		if (symbol != IDENFR) {  //���Ǳ�ʶ��
			return false;
		}
		doOutput();  //�Ǳ�ʶ��
		name = string(token);
		if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
			if (localSymbolTable[name].kind == 2) {  //const
				errorfile << line << " j\n";  //�ı䳣����ֵ��
				error = true;
			}
		}
		else {
			if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
				if (globalSymbolTable[name].kind == 2) {  //const
					errorfile << line << " j\n";  //�ı䳣����ֵ��
					error = true;
				}
			}
			else {
				errorfile << line << " c\n";  //δ���������
				error = true;
			}
		}
		string nameLeft = name;
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != ASSIGN) {  //����=
			return false;
		}
		doOutput();   //��=
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != IDENFR) {  //���Ǳ�ʶ��
			return false;
		}
		doOutput();  //�Ǳ�ʶ��
		name = string(token);
		if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
			if (localSymbolTable[name].kind == 2) {  //const
				errorfile << line << " j\n";  //�ı䳣����ֵ��
				error = true;
			}
		}
		else {
			if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
				if (globalSymbolTable[name].kind == 2) {  //const
					errorfile << line << " j\n";  //�ı䳣����ֵ��
					error = true;
				}
			}
			else {
				errorfile << line << " c\n";  //δ���������
				error = true;
			}
		}
		string nameRight = name;
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol != PLUS && symbol != MINU) { //����+ -
			return false;
		}
		bool isPLUS = (symbol == PLUS);
		doOutput();  //��+-
		re = getsym();
		if (re < 0) {
			return false;
		}
		int conInt;
		if (!step(conInt)) {  //��������
			return false;
		}
		string stepNum = int2string(conInt);
		//���������ɹ� ��Ԥ����һ������
		if (symbol != RPARENT) {
			retractString(oldIndex);
			errorfile << line << " l\n";  //ȱ����С����
			error = true;
			symbol = RPARENT;
		}
		if (symbol != RPARENT) {  //����)
			return false;
		}
		doOutput();  //��)
		re = getsym();
		if (re < 0) {
			return false;
		}
		if (!statement()) {  //�������
			return false;
		}
		midCodeTable.push_back(midCode(isPLUS ? PLUSOP : MINUOP, nameLeft, nameRight, stepNum));  //���Ӳ���
		//midCodeTable.push_back(midCode(GOTO, lbegin, "", ""));  //�ص�lbegin ���������ж�
		/*for (int ix = conditionBeginIndex; ix < conditionEndIndex; ix++) {
			midCode mc = midCodeTable[ix];
			midCodeTable.push_back(mc);
		}*/
		map<string, string> nMap;
		for (int ix = conditionBeginIndex; ix < conditionEndIndex; ix++) {
			midCode mc = midCodeTable[ix];
			if (mc.x[0] == '#' && nMap.find(mc.x) == nMap.end()) {
				nMap[mc.x] = genTmp();
			}
			if (mc.y[0] == '#' && nMap.find(mc.y) == nMap.end()) {
				nMap[mc.y] = genTmp();
			}
			if (mc.z[0] == '#' && nMap.find(mc.z) == nMap.end()) {
				nMap[mc.z] = genTmp();
			}
			if (mc.x[0] == '%' && nMap.find(mc.x) == nMap.end()) {
				nMap[mc.x] = genName();
			}
			if (mc.y[0] == '%' && nMap.find(mc.y) == nMap.end()) {
				nMap[mc.y] = genName();
			}
			if (mc.z[0] == '%' && nMap.find(mc.z) == nMap.end()) {
				nMap[mc.z] = genName();
			}
		}
		for (int ix = conditionBeginIndex; ix < conditionEndIndex; ix++) {
			midCode mc = midCodeTable[ix];
			if (mc.x[0] == '#' || mc.x[0] == '%') {
				mc.x = nMap[mc.x];
			}
			if (mc.y[0] == '#' || mc.y[0] == '%') {
				mc.y = nMap[mc.y];
			}
			if (mc.z[0] == '#' || mc.z[0] == '%') {
				mc.z = nMap[mc.z];
			}
			midCodeTable.push_back(mc);
		}
		for (map<string, string>::iterator it = nMap.begin(); it != nMap.end(); it++) {
			string oriName = (*it).first;
			string newName = (*it).second;
			symbolItem sitem = localSymbolTable[oriName];
			sitem.name = newName;
			sitem.addr = localAddr;
			localAddr++;
			localSymbolTable.insert(make_pair(newName, sitem));
		}
		midCodeTable.push_back(midCode(BNZ, forBody, "<>", ""));  //�ص�forBody
		midCodeTable.push_back(midCode(LABEL, lend, "", ""));  //lend����ѭ��
		//�������ɹ� ��Ԥ����һ������
		outputfile << "<ѭ�����>" << endl;
		return true;
	}
	else {
		return false;
	}
}

//��������::= ���޷���������
bool step(int& value) {
	if (unsignedInteger(value)) {
		outputfile << "<����>" << endl;
		return true;
	}
	else {
		return false;
	}
}

void fullNameMap(map<string, string>& nameMap, vector<midCode> ve, string funcName) {
	for (int i = 0; i < ve.size(); i++) {
		midCode mc = ve[i];
		switch (mc.op) {
		case PLUSOP:
		case MINUOP:
		case MULTOP:
		case DIVOP:
		case GETARRAY:  //mc.z << " = " << mc.x << "[" << mc.y << "]
		case PUTARRAY:  //mc.z << "[" << mc.x << "]" << " = " << mc.y
			if (allLocalSymbolTable[funcName].find(mc.z) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.z) == nameMap.end()) {
				if (mc.z[0] == '#') {
					nameMap[mc.z] = genTmp();
				}
				else {
					nameMap[mc.z] = genName();
				}
			}
			if (allLocalSymbolTable[funcName].find(mc.y) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.y) == nameMap.end()) {
				if (mc.y[0] == '#') {
					nameMap[mc.y] = genTmp();
				}
				else {
					nameMap[mc.y] = genName();
				}
			}
			if (allLocalSymbolTable[funcName].find(mc.x) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.x) == nameMap.end()) {
				if (mc.x[0] == '#') {
					nameMap[mc.x] = genTmp();
				}
				else {
					nameMap[mc.x] = genName();
				}
			}
			break;
		case LSSOP:
		case LEQOP:
		case GREOP:
		case GEQOP:
		case EQLOP:
		case NEQOP:
			if (allLocalSymbolTable[funcName].find(mc.y) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.y) == nameMap.end()) {
				if (mc.y[0] == '#') {
					nameMap[mc.y] = genTmp();
				}
				else {
					nameMap[mc.y] = genName();
				}
			}
			if (allLocalSymbolTable[funcName].find(mc.x) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.x) == nameMap.end()) {
				if (mc.x[0] == '#') {
					nameMap[mc.x] = genTmp();
				}
				else {
					nameMap[mc.x] = genName();
				}
			}
			break;
		case ASSIGNOP:
			if (allLocalSymbolTable[funcName].find(mc.z) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.z) == nameMap.end()) {
				if (mc.z[0] == '#') {
					nameMap[mc.z] = genTmp();
				}
				else {
					nameMap[mc.z] = genName();
				}
			}
			if (allLocalSymbolTable[funcName].find(mc.x) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.x) == nameMap.end()) {
				if (mc.x[0] == '#') {
					nameMap[mc.x] = genTmp();
				}
				else {
					nameMap[mc.x] = genName();
				}
			}
			break;
		case GOTO:
		case BZ:
		case BNZ:
		case LABEL:
			if (allLocalSymbolTable[funcName].find(mc.z) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.z) == nameMap.end()) {
				nameMap[mc.z] = genLabel();
			}
			break;
		case RET:
		case INLINERET:
		case SCAN:
			if (allLocalSymbolTable[funcName].find(mc.z) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.z) == nameMap.end()) {
				if (mc.z[0] == '#') {
					nameMap[mc.z] = genTmp();
				}
				else {
					nameMap[mc.z] = genName();
				}
			}
			break;
		case PUSH:
		case CALL:
		case RETVALUE:
			break;
		case PRINT:
			if (mc.x == "1" || mc.x == "2") {
				if (allLocalSymbolTable[funcName].find(mc.z) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
					nameMap.find(mc.z) == nameMap.end()) {
					if (mc.z[0] == '#') {
						nameMap[mc.z] = genTmp();
					}
					else {
						nameMap[mc.z] = genName();
					}
				}
			}
			break;
		case CONST:
		case ARRAY:
		case VAR:
		case PARAM:
			if (allLocalSymbolTable[funcName].find(mc.x) != allLocalSymbolTable[funcName].end() &&  //�ֲ�����
				nameMap.find(mc.x) == nameMap.end()) {
				if (mc.x[0] == '#') {
					nameMap[mc.x] = genTmp();
				}
				else {
					nameMap[mc.x] = genName();
				}
			}
			break;
		case FUNC:
		case EXIT:
			break;
		default:
			break;
		}
	}
}

void dealInlineFunc(string name, int& begin, int& end) {
	vector<midCode> ve = funcMidCodeTable[name];  //����������е��м����
	//����������Ҫ�޸����������ߵı�����������������
	map<string, string> nameMap;
	begin = nameId + 1;
	fullNameMap(nameMap, ve, name);
	end = nameId;
	//for (map<string, string>::iterator it = nameMap.begin(); it != nameMap.end(); it++) {
	//	cout << (*it).first << "->" << (*it).second << "\n";
	//}
	//���θĳɸ�ֵ
	int paramSize = globalSymbolTable[name].parameterTable.size();  //��������
	for (int i = midCodeTable.size() - 1, j = paramSize; i >= 0; i--) {
		if (midCodeTable[i].op == PUSH && midCodeTable[i].y == name) {  //��һ������midCodeTable����󼸸���PUSH
			midCodeTable[i].op = ASSIGNOP;
			midCodeTable[i].x = midCodeTable[i].z;
			midCodeTable[i].z = nameMap[ve[j].x];
			midCodeTable[i].y = "";
			j--;
			if (j == 0) {
				break;
			}
		}
	}
	//�ĸ�������
	for (int i = paramSize + 1; i < ve.size(); i++) {
		midCode mc = ve[i];
		if (nameMap.find(mc.z) != nameMap.end()) {
			mc.z = nameMap[mc.z];
		}
		if (nameMap.find(mc.x) != nameMap.end()) {
			mc.x = nameMap[mc.x];
		}
		if (nameMap.find(mc.y) != nameMap.end()) {
			mc.y = nameMap[mc.y];
		}
		if (mc.op == RET) {
			if (mc.z == "") { //�޷���ֵ����
				break;  //������continue ���ǵ���RET ��߾�û�� ֱ��break
			}
			else {
				mc.op = INLINERET;
			}
		}
		midCodeTable.push_back(mc);
		if (mc.op == RET) {
			break;
		}
	}
	//���ű�Ҳ�ø�
	for (map<string, symbolItem>::iterator it = allLocalSymbolTable[name].begin(); it != allLocalSymbolTable[name].end(); it++) {
		symbolItem si = (*it).second;
		si.addr = localAddr;
		if (si.kind == 4) {  //��������
			localAddr += si.length;
		}
		else {
			localAddr++;
		}
		if (nameMap.find(si.name) != nameMap.end()) {
			si.name = nameMap[si.name];
		}
		localSymbolTable.insert(make_pair(si.name, si));
	}
}

//���з���ֵ����������䣾 ::= ����ʶ����'('��ֵ������')��
//���ڵ�д�� һ��������������� ��ô������������ǺϷ��� ��������ȫ�ֱ� ��������ֲ��� �� ����ֵ��int/char
bool callHaveReturnValueFunction() {
	if (symbol == IDENFR) {  //��ʶ���Ǻ����� ��Ҫ��ȫ�ַ��ű�
		string name = string(token);
		//midCodeTable.push_back(midCode(CALL, name, "", ""));
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //��(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			//��ʼ����ֵ������
			if (!valueParameterTable(name)) {
				return false;
			}
			//����ֵ������ɹ� ��Ԥ����һ������
			if (symbol != RPARENT) {
				retractString(oldIndex);
				errorfile << line << " l\n";  //ȱ����С����
				error = true;
				symbol = RPARENT;
			}
			if (symbol == RPARENT) {  //��)
				doOutput();
				if (funcInlineAble[name]) {  //������������
					int be, en;
					dealInlineFunc(name, be, en);
					midCodeTable.push_back(midCode(INLINEEND, int2string(be), int2string(en), ""));
				}
				else {
					midCodeTable.push_back(midCode(CALL, name, "", ""));
				}
				outputfile << "<�з���ֵ�����������>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//���޷���ֵ����������䣾 ::= ����ʶ����'('��ֵ������')��
//���ڵ�д�� һ��������������� ��ô������������ǺϷ��� ��������ȫ�ֱ� ��������ֲ��� �� ����ֵ��void
bool callNoReturnValueFunction() {
	if (symbol == IDENFR) {  //��ʶ��
		string name = string(token);
		//midCodeTable.push_back(midCode(CALL, name, "", ""));
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //��(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			//��ʼ����ֵ������
			if (!valueParameterTable(name)) {
				return false;
			}
			//����ֵ������ɹ� ��Ԥ����һ������
			if (symbol != RPARENT) {
				retractString(oldIndex);
				errorfile << line << " l\n";  //ȱ����С����
				error = true;
				symbol = RPARENT;
			}
			if (symbol == RPARENT) {  //��)
				doOutput();
				if (funcInlineAble[name]) {  //������������
					int be, en;
					dealInlineFunc(name, be, en);
					midCodeTable.push_back(midCode(INLINEEND, int2string(be), int2string(en), ""));
				}
				else {
					midCodeTable.push_back(midCode(CALL, name, "", ""));
				}
				outputfile << "<�޷���ֵ�����������>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//��ֵ������  ::= �����ʽ��{,�����ʽ��}�����գ�
bool valueParameterTable(string funcName) {
	//ֵ���������Ϊ��  ֵ������Ϊ��ʱ ��ǰ�ַ�����)������
	/*if (symbol == RPARENT) {
		if (globalSymbolTable[funcName].parameterTable.size() != 0) {
			errorfile << line << " d\n";  //����������ƥ��
			error = true;
		}
		outputfile << "<ֵ������>" << endl;
		return true;
	}*/
	vector<int> typeList;  //ֵ��������
	int type;
	string value;
	if (!expression(type, value)) {  //���÷������ʽ
		//if (symbol == RPARENT) {  //˵��ֵ������Ϊ��  ����)˵��ȱ��������
		if (globalSymbolTable[funcName].parameterTable.size() != 0) {
			errorfile << line << " d\n";  //����������ƥ��
			error = true;
		}
		outputfile << "<ֵ������>" << endl;
		return true;
	}
	typeList.push_back(type);
	midCodeTable.push_back(midCode(PUSH, value, "", funcName));
	//�������ʽ�ɹ� ��Ԥ����һ������
	//��ʼ����{,�����ʽ��}
	while (true) {
		if (isEOF()) {
			break;
		}
		if (symbol != COMMA) {  //���Ƕ���
			break;
		}
		//��ǰ�Ƕ��� ����һ���ǲ��Ǳ��ʽ
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (!expression(type, value)) {  //���÷������ʽ
			return false;
		}
		//�������ʽ�ɹ� ��Ԥ����һ������
		typeList.push_back(type);
		midCodeTable.push_back(midCode(PUSH, value, "", funcName));
	}
	if (typeList.size() != globalSymbolTable[funcName].parameterTable.size()) {
		errorfile << line << " d\n";  //����������ƥ��
		error = true;
	}
	else {
		for (int i = 0; i < typeList.size(); i++) {
			if (typeList[i] != globalSymbolTable[funcName].parameterTable[i]) {
				errorfile << line << " e\n";  //�������Ͳ�ƥ��
				error = true;
				break;
			}
		}
	}
	outputfile << "<ֵ������>" << endl;
	return true;
}

//������У�   ::= ������䣾��
bool statementList() {
	while (symbol != RBRACE) {  //while (true)
		if (!statement()) {  //�ж��ǲ������
			break;
		}
	}
	outputfile << "<�����>" << endl;
	return true;   //?????�����һ�ν�while�Ͳ������ �᲻�������⣿
}

//������䣾    ::=  scanf '('����ʶ����{,����ʶ����}')��
bool readStatement() {
	if (symbol == SCANFTK) {
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //��(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (symbol == IDENFR) {
				string name = string(token);
				if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
					if (localSymbolTable[name].kind == 2) {  //const
						errorfile << line << " j\n";  //�ı䳣����ֵ��
						error = true;
					}
				}
				else {
					if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
						if (globalSymbolTable[name].kind == 2) {  //const
							errorfile << line << " j\n";  //�ı䳣����ֵ��
							error = true;
						}
					}
					else {
						errorfile << line << " c\n";  //δ���������
						error = true;
					}
				}
				midCodeTable.push_back(midCode(SCAN, name, "", ""));
				doOutput();
				//��ʼ����{,����ʶ����}
				while (true) {
					re = getsym();
					if (re < 0) {
						return false;
					}
					if (symbol != COMMA) {  //����,
						break;
					}
					//��ǰ�Ƕ��� ����һ���ǲ��Ǳ�ʶ��
					doOutput();
					re = getsym();
					if (re < 0) {
						return false;
					}
					if (symbol != IDENFR) {//��ʶ��
						return false;
					}
					//��ǰ�Ǳ�ʶ��
					name = string(token);
					if (localSymbolTable.find(name) != localSymbolTable.end() && localSymbolTable[name].kind != 3) {
						if (localSymbolTable[name].kind == 2) {  //const
							errorfile << line << " j\n";  //�ı䳣����ֵ��
							error = true;
						}
					}
					else {
						if (globalSymbolTable.find(name) != globalSymbolTable.end() && globalSymbolTable[name].kind != 3) {
							if (globalSymbolTable[name].kind == 2) {  //const
								errorfile << line << " j\n";  //�ı䳣����ֵ��
								error = true;
							}
						}
						else {
							errorfile << line << " c\n";  //δ���������
							error = true;
						}
					}
					midCodeTable.push_back(midCode(SCAN, name, "", ""));
					doOutput();
				}
				if (symbol != RPARENT) {
					retractString(oldIndex);
					errorfile << line << " l\n";  //ȱ����С����
					error = true;
					symbol = RPARENT;
				}
				if (symbol == RPARENT) {  //)
					doOutput();
					outputfile << "<�����>" << endl;
					getsym();  //Ԥ��һ�� ������ɶ
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//��д��䣾    ::= printf '(' ���ַ�����,�����ʽ�� ')'| printf '('���ַ����� ')'| printf '('�����ʽ��')��
bool writeStatement() {
	if (symbol == PRINTFTK) {
		doOutput();
		int re = getsym();
		if (re < 0) {
			return false;
		}
		if (symbol == LPARENT) {  //��(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			if (strings()) {  //�ַ�������  Ԥ��һ������
				string smodify = string(s);
				int p=-2;
				while ((p = smodify.find("\\", p+2)) != string::npos) {
					smodify.replace(p, 1, "\\\\");
				}
				stringList.push_back(smodify);
				if (symbol == COMMA) {  //,  printf '(' ���ַ�����,�����ʽ�� ')'
					midCodeTable.push_back(midCode(PRINT, smodify, "3", ""));
					doOutput();
					re = getsym();
					if (re < 0) {
						return false;
					}
					int t;
					string value;
					if (!expression(t, value)) {  //�������ʽ
						return false;
					}
					midCodeTable.push_back(midCode(PRINT, value, int2string(t), ""));
					//�������ʽ�ɹ� ��Ԥ����һ������
					if (symbol != RPARENT) {
						retractString(oldIndex);
						errorfile << line << " l\n";  //ȱ����С����
						error = true;
						symbol = RPARENT;
					}
					if (symbol == RPARENT) {  //)
						doOutput();
						midCodeTable.push_back(midCode(PRINT, "EndLine", "4", ""));
						outputfile << "<д���>" << endl;
						getsym();  //Ԥ��һ�� ������ɶ
						return true;
					}
					else {
						return false;
					}
				}
				else {
					if (symbol != RPARENT) {
						retractString(oldIndex);
						errorfile << line << " l\n";  //ȱ����С����
						error = true;
						symbol = RPARENT;
					}
					if (symbol == RPARENT) {  //)  printf '('���ַ����� ')'
						doOutput();
						midCodeTable.push_back(midCode(PRINT, smodify, "3", ""));
						midCodeTable.push_back(midCode(PRINT, "EndLine", "4", ""));
						outputfile << "<д���>" << endl;
						getsym();  //Ԥ��һ�� ������ɶ
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {  //�ж��ǲ��Ǳ��ʽ  printf '('�����ʽ��')��
				int t;
				string value;
				if (!expression(t, value)) {  //�������ʽ
					return false;
				}
				midCodeTable.push_back(midCode(PRINT, value, int2string(t), ""));
				//�������ʽ�ɹ� ��Ԥ����һ������
				if (symbol != RPARENT) {
					retractString(oldIndex);
					errorfile << line << " l\n";  //ȱ����С����
					error = true;
					symbol = RPARENT;
				}
				if (symbol == RPARENT) {  //)
					doOutput();
					midCodeTable.push_back(midCode(PRINT, "EndLine", "4", ""));
					outputfile << "<д���>" << endl;
					getsym();  //Ԥ��һ�� ������ɶ
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//��������䣾   ::=  return['('�����ʽ��')']  
bool returnStatement() {
	if (symbol == RETURNTK) {  //return 
		int type;
		doOutput();
		//��ʼ���� ['('�����ʽ��')']    ���п��޵�
		int re = getsym();
		if (re < 0) {   // ��߿���û��
			type = 3;
			realReturnType = type;
			if (curFuncReturnType == 1 || curFuncReturnType == 2) {
				errorfile << line << " h\n";  //�з���ֵ�ĺ������ڲ�ƥ���return���
				error = true;
			}
			outputfile << "<�������>" << endl;
			return true;
		}
		if (symbol == LPARENT) {  //��(
			doOutput();
			re = getsym();
			if (re < 0) {
				return false;
			}
			string value;
			if (!expression(type, value)) {  //�������ʽ return�ķ������;��Ǳ��ʽ������
				return false;
			}
			realReturnType = type;
			//�������ʽ�ɹ� ��Ԥ����һ������
			if (curFuncReturnType == 3) {
				errorfile << line << " g\n";  //�޷���ֵ�ĺ������ڲ�ƥ���return���
				error = true;
			}
			else if (curFuncReturnType == 1 || curFuncReturnType == 2) {
				if (curFuncReturnType != type) {
					errorfile << line << " h\n";  //�з���ֵ�ĺ������ڲ�ƥ���return���
					error = true;
				}
			}
			if (symbol != RPARENT) {
				retractString(oldIndex);
				errorfile << line << " l\n";  //ȱ����С����
				error = true;
				symbol = RPARENT;
			}
			if (symbol == RPARENT) {  //)
				doOutput();
				if (!isMain) {
					midCodeTable.push_back(midCode(RET, value, "", ""));
				}
				else {
					midCodeTable.push_back(midCode(EXIT, "", "", ""));
				}
				outputfile << "<�������>" << endl;
				getsym();  //Ԥ��һ�� ������ɶ
				return true;
			}
			else {
				return false;
			}
		}
		else {  //return ��߲���( Ҳ���� 
			type = 3;
			realReturnType = type;
			if (curFuncReturnType == 1 || curFuncReturnType == 2) {
				errorfile << line << " h\n";  //�з���ֵ�ĺ������ڲ�ƥ���return���
				error = true;
			}
			if (!isMain) {
				midCodeTable.push_back(midCode(RET, "", "", ""));
			}
			else {
				midCodeTable.push_back(midCode(EXIT, "", "", ""));
			}
			outputfile << "<�������>" << endl;
			return true;
		}
	}
	else {
		return false;
	}
}

int getsym()
{
	char ch=getchar();
	int symbol=0;
	while(isSpace(ch)||isNewline(ch)||isTab(ch))
		ch=getchar();
	if(isLetter(ch))
	{
		string s;
		while(isLetter((ch))
		{
			s=s+ch;
			ch=getchar();
		}
		for(auto t:reserve)
		{
			if(s==t) symbol=mp[t];
		}
	}
	return 0;
}

# SOFIA Example
The program is "lexically" correct and should not generate any error (based on Platypus from Svillen Ranev) #
main& {
	data {
		int i$;
		real a%, sum008%;
		string text@;
	}
	code {
		a%=+1.2;
		sum008% = 7.87050 ;
		input&(a%,sum008%);
		i$=0;
		while (i$ < 32767 .or. i$ == 32767)do{
			i$ = i$ + 2;
			a% = a% * i$/0.5 ;
			sum008% = sum008% + a% - 1 ;
		};
		if (text@ == '')then {
			text@ = 'prog' ++ 'ram';
		}
		else {
			text@ = text@ ++ 'ram';
		};
		print&('\* This is a program -:)-<-<-- \*');
		print&(text@);
		if (text@ <> 'program' .and. sum008%==8.0 .or. i$>10)then {
			print&(sum008%);
			print&();
		}
		else{};
	}
}

/*
	The chance function needed a home in a .h file so I could use it.
	
	Remove it if you feel necessary.

	Liam Irish

*/


bool chance(int num)
{
    if (number_range(1,100) <= num) return TRUE;
    else return FALSE;
}     

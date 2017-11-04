Title of the project: FILE i/o Library Functions

Name: Shreyas Shyamprasad Ambekar

MIS ID: 111603002

Description of work done: 
	Starting with elaborate reading of man pages, my project work progressed with understanding of buffer, creating FILE data 
structure, actual coding, pushing it on gitlab regularly and finally testing all the functions.
	As my project was implementing library functions, I was supposed to have thorough understading of the functions. So, along with
reading linux man pages, I read their standard description on http://pubs.opengroup.org/. The next task was to create the FILE data 
structure. So, I listed down the members that I would require in FILE data structure that would make my functions work. I also referred 
'The Unix System Interface' chapter from KnR while creating FILE data structure.The next most important part of my project was to 
understand working of buffer. Making buffer work was the most interesting part of project. It led me to understand that if a function 
fails, it may not be because of failure of its corresponding low level function. It can also fail because of failure of other functions.  
e.g. If fread fails, it may not be basically because failure of underlying read operation. It can also fail because of underlying write 
operation which takes place because of buffered i/o. Similar was the case for fwrite, fseek, fclose functions. Also, the interesting thing 
was that you had not to actually use lseek while you use fseek. Just changing buffer index could do your work. So, there were many fun 
things like the mentioned above while handling buffer. I also had to learn some detailed theorotical information about system calls like 
"The result of using O_TRUNC with O_RDONLY is undefined". A simple theorotical statement I missed was giving me errors and I was reading 
the whole code for an hour to see what had gone wrong. I learnt gitlab and pushed my code on gitlab as soon as I had made any changes. At 
last testing part was done considering the maximum possible test cases.
	It was my first time to manage code on this much big scale. It really increased my coding experience. It also increased my 
theorotical information about input, output functions, linux system calls, general information about linux, gitlab, etc. So, overall it 
was a very nice experience to do the project and opportunity to learn through it.

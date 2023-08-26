package kw.kimsangwoo.assign4; //package name
import java.util.*;			   //import about vector, scanner, tokenizer.. etc
import java.io.*;			   //import about i/o
class Member{					//new class about each person
	private String name;		//private variables about name,age,salary
	private int age;
	private int salary;
	public Member(String str, int a, int b){//when create, we need to set values
		this.name=str;
		this.age=a;
		this.salary=b;
	}
	public String memstr() {				//string to save text file 
		return (this.name+" / "+this.age+" / "+this.salary);
	}
	public String memstr2() {				//string to save text file 
		return (this.name+","+this.age+","+this.salary);
	}
	public String getname(){				//return class's name
		return this.name;
	}
	public int getage(){					//return age's name
		return this.age;
	}
	public int getsalary(){					//return salary's name
		return this.salary;
	}
}

class comname implements Comparator<Member>{				//class comname use interface comparator
	public int compare(Member m1, Member m2) {				//sorted in descending about name first, salary second
		if(((m1.getname()).compareTo(m2.getname()))<0) {	//m1.name is faster
			return 1;
		}
		else if(((m1.getname()).compareTo(m2.getname()))>0) {//m2.name is faster
			return -1;
		}
		else{												//name equals
			if(m1.getsalary()>m2.getsalary()) {				//m1.salary is bigger
				return -1;
			}
			else {
				return 1;
			}
		}
	}
}
class comint implements Comparator<Member>{					//class comint use interface comparator
	public int compare(Member m1, Member m2) {				//sorted in ascending about name first, salary second
		if(m1.getsalary()>m2.getsalary()) {					//m1.salary is bigger
			return 1;
		}
		else if(m1.getsalary()<m2.getsalary()) {			//m2.salary is bigger
			return -1;
		}
		else{												//salary equals
			if(((m1.getname()).compareTo(m2.getname()))<0) {//m1.name is faster
				return -1;
			}
			else {											//m2.name is faster or equal
				return 1;
			}
		}
	}
}
public class assign4 {
	public static void main(String[] args) throws IOException{//main method
		Vector<Member> sallist= new Vector<Member>();		  //make vector to save member
		File file = new File(".");							  //to find current project
		String rootPath = System.getProperty("user.dir");	  //to find current project
		File f= new File(rootPath+"\\Salaries.txt");		  //road to take certain txt file
		Scanner scanner = new Scanner(System.in);			  //scanner to write
		while(true) {
			System.out.println("===============================================================================");
			System.out.println("1.Load  2.Insert  3.Delete  4.Update  5.Sort  6.Save");
			System.out.println("===============================================================================");
			//print format
			System.out.print("Select Method: ");	
			int input = scanner.nextInt();			//take input
			if(input==1) {							//if user selects 1.Load
				if(!f.exists()) {					//file isn't exist
					System.out.println("File not exist");//error print
					continue;						//return to input timing
				}
				Scanner fileread = new Scanner(f);	//variable to read txt file
				while(fileread.hasNext()) {			//check string exist
					String str = fileread.next();	//take string from txt file
					StringTokenizer st= new StringTokenizer(str, ",");	
					while(st.hasMoreTokens()) {							
						Member mem1=new Member(st.nextToken(),Integer.parseInt(st.nextToken()),Integer.parseInt(st.nextToken()));
						sallist.add(mem1);		//cut string by , and take values
					}
				}
				fileread.close();					//scanner close
				System.out.println("Load success");	//success print
			}
			if(input==2) {							//user selects 2. Insert
				System.out.print("이름 입력 : ");		//take name and age from user
				String name = scanner.next();
				System.out.print("나이 입력 : ");
				int age = scanner.nextInt();		
				int excheck=0;						//exist check
				for(Member a: sallist ) {			//take member objects from vector
					if(name.equals(a.getname())) {  //equal check of name, age
						if(age==a.getage()) {		//if object exist
							excheck=1;				
							System.out.println("Already exist");//print error
							break;
						}
					}
				}
				if(excheck==0) {					//if object not exist
					System.out.print("연봉 입력 : ");	
					int sala = scanner.nextInt();	//take salary
					Member mem1=new Member(name,age,sala);//make new Member object
					sallist.add(mem1);					  //add Member oject to vector
					for(int j=0;j<sallist.size();j++) {	  //print vector's every contents
						System.out.println(sallist.get(j).memstr());
					}
				}
			}
			if(input==3) {						//user selects 2. Insert
				System.out.print("이름 입력 : ");	//take name and age from user
				String name = scanner.next();
				System.out.print("나이 입력 : ");
				int age = scanner.nextInt();
				int excheck=0;					//exist check
				for(int i=0;i<sallist.size();i++ ) {				//during vector
					if(name.equals(sallist.get(i).getname())) {		//check name equals
						if(age==sallist.get(i).getage()) {			//check salary equals
							excheck=1;								
							sallist.remove(i);						//remove Member in vector
							break;
						}
					}
				}
				if(excheck==0) {									//error check if object no exist
					System.out.println("Not exist");
				}
				else {												//print vector's all contents if object existed 
					for(int j=0;j<sallist.size();j++) {
						System.out.println(sallist.get(j).memstr());
					}
				}
			}
			if(input==4) {						//user selects 2. Insert
				System.out.print("이름 입력 : ");	//take name and age from user
				String name = scanner.next();
				System.out.print("나이 입력 : ");
				int age = scanner.nextInt();
				int excheck=0;									//exist check
				for(int i=0;i<sallist.size();i++ ) {			//during vector
					if(name.equals(sallist.get(i).getname())) {	//check name equals
						if(age==sallist.get(i).getage()) {		//check salary equals
							excheck=1;
							System.out.print("연봉 입력 : ");
							int salary = scanner.nextInt();				//take salary from user
							Member mem1=new Member(name, age,salary);	//make new Object to update
							sallist.set(i,mem1);						//update Object in vector
							break;
						}
					}
				}
				if(excheck==0) {										//error check if object is not exist
					System.out.println("Not exist");
				}
				else {													//print vector's all contents if object existed
					for(int j=0;j<sallist.size();j++) {
						System.out.println(sallist.get(j).memstr());
					}
				}
			}
			if(input==5) {									//user selects 2. Insert
				System.out.print("1.Name 2.Salary : ");		//take option select from user
				int sel = scanner.nextInt();
				if(sel==1) {								//name sort (descending)
					Collections.sort(sallist, new comname());
				}
				else if(sel==2) {							//salary sort (ascending)
					Collections.sort(sallist, new comint()); 
				}
				for(int j=0;j<sallist.size();j++) {			//print vector's all contents if object existed
					System.out.println(sallist.get(j).memstr());
				}
			}
			if(input == 6) {								//if user select 6.Save
				if(!file.exists()) {						//file isn't exist
					file.createNewFile();					//make file
				}
				FileWriter writer= new FileWriter(f);		//variables to write vector contents in txt file
				BufferedWriter wrbuf = new BufferedWriter(writer);
				for(int j=0;j<sallist.size();j++) {			//take vector contents and write in txt file
					wrbuf.write(sallist.get(j).memstr2());
					wrbuf.newLine();						//change line to file format
				}
				wrbuf.close();								//close BufferedWriter
				System.out.println("Save success");			//success check
				break;										//stop to write input
			}
		}	
		scanner.close();									//scanner close
		System.out.println("Program terminate");			//program terminated
	}
}

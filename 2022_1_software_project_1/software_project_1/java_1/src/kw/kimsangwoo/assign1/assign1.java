package kw.kimsangwoo.assign1;	//package name
import java.util.Scanner;		//for scanner
import java.util.Vector;		//for Vector
public class assign1 {			
	public static int gcd(int a, int b) {//take greatest common divisor(Euclidean algorithm)
		if(a%b==0) {					 //repeat to remainder=0
			return b;
		}
		return gcd(b,a%b);				 //recursive GDC function
	}
	public static void main(String[] args) {		//main function that makes result
		Scanner scanner = new Scanner(System.in);	//take scanner variable
		Vector<Integer> inputVec = new Vector<Integer>();//take input in inputVector
		System.out.print("INPUT : ");				//call user to input
		int n = scanner.nextInt();					//take input number
		if(n!=0){									//not exit at first input
			inputVec.add(n);						//Vector take input
			int gcd=n;								//put input in gcd
			int lcn=n;								//put input in lcn
			System.out.println("Input Numbers : "+n);//output format for number
			System.out.println("LCN : "+lcn);		//output format for lcn
			System.out.println("GCD : "+gcd);		//output format for gcd
			while(true){							//infinity loop
				System.out.print("INPUT : ");		//call user to take new input
				n = scanner.nextInt();				//take input
				if(n==0){							//if n equal 0
					break;							//loop end
				}
				inputVec.add(n);					//new value in vector
				System.out.print("Input Numbers : ");//format to print vector value(in order)
				for(int i=0;i<inputVec.size();i++) {//loop to print vector
					if(i!=0) {
						System.out.print(",");		//print format
					}
					System.out.print(inputVec.get(i));//print value in vector
				}
				System.out.println();				//line change
				
				if(lcn>n)lcn=(lcn*n/gcd(lcn,n));	//make lcn between pre-lcn and new input
				else lcn=(lcn*n/gcd(n,lcn));		//(using gcd)
				System.out.println("LCN : "+lcn);	//print new lcn value
				
				if(gcd>n)gcd=gcd(gcd,n);			//make gcd between pre-gcd and new input
				else gcd=gcd(n,gcd);				
				System.out.println("GCD : "+gcd);	//print new gcd
			}
		}
		scanner.close();							//scanner close
	}
}

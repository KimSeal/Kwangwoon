package kw.kimsangwoo.assign2;		//package name
import java.util.Scanner;			//for scanner
import java.util.Vector;			//for vector
import java.util.StringTokenizer;	//for cut string use tokenizer

public class assign2 {
	public static void main(String[] args) {//main function that make result
		Scanner scanner = new Scanner(System.in);	//scanner to take input
		while(true) {
			System.out.print("input : ");//infinity loop
			String inputstr = (scanner.next());		//take input
			if(inputstr.equals("0")) {				//exit check
				break;								//stop loop
			}
			StringTokenizer st= new StringTokenizer(inputstr, ","); //take height
			int n=0;												//current height
			int high=0;												//max height+1(to print)
			Vector<Integer> Vec = new Vector<Integer>();			//vector to save road
			while(st.hasMoreTokens()) {								//check next token exist
				int height=Integer.parseInt(st.nextToken());		//take target height
				if(high<height)high=height;							//control print max height
				while(true) {										//make n to height 1 by 1
					if(n>height)n--;								//if height is smaller than n
					else if(n<height)n++;							//if height is smaller than n
					Vec.add(n);										//add n to print
					if(n==height)break;								//when n=height, break
				}
			}
			while(true) {											//make n to 1
				if(n==1)break;
				n--;
				Vec.add(n);											//to finish at 1
			}
			for(int i=high+1;i>0;i--) {								//print mountain :max height+1
				for(int j=0;j<Vec.size();j++) {						//width
					if(i<=Vec.get(j)) {								//at mountain
						System.out.print("@");
					}
					else {											//at sky
						System.out.print("'");
					}
				}
				System.out.println();								//line change
			}
		}
		scanner.close();
	}
}

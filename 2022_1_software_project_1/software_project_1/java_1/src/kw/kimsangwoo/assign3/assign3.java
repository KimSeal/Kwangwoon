package kw.kimsangwoo.assign3;			//package name
import java.util.Calendar;				//use calendar
import java.util.Scanner;				//use scanner

class mycal{							//new class for print calendar
	Calendar cal1;						//calendars to print 4*3 format
	Calendar cal2;					
	Calendar cal3;
	int i1;								//current day
	int weekday1;						//currrent day of week
	int maxDay1;						//current month's last day
	int i2;								//day of next month
	int weekday2;						//day of week of next month
	int maxDay2;						//last day of next month
	int i3;								//day of month+2
	int weekday3;						//day of week of month+2
	int maxDay3;						//last day of month+2
	public void setcal(int year, int month) {	//set calendar
		this.cal1.set(year,month-1,1);			//take calendar about 3month
		this.cal2.set(year,month,1);
		this.cal3.set(year,month+1,1);
		System.out.printf("%-21s",(this.cal1.get(Calendar.MONTH)+1+"월"));	//print format about
		System.out.printf("  %-21s",(this.cal2.get(Calendar.MONTH)+1+"월"));	//month, day of week
		System.out.printf("  %-21s\n",(this.cal3.get(Calendar.MONTH)+1+"월"));
		System.out.print("일  월  화  수  목  금  토 |");
		System.out.print("일  월  화  수  목  금  토 |");
		System.out.println("일  월  화  수  목  금  토");
	    this.i1=1; this.i2=1; this.i3=1;									//initialize day of months
	    this.maxDay1 = this.cal1.getActualMaximum(Calendar.DAY_OF_MONTH);	//take last day of months
	    this.weekday1=cal1.get(Calendar.DAY_OF_WEEK);						//take day of week of each months's first day
	    this.maxDay2 = this.cal2.getActualMaximum(Calendar.DAY_OF_MONTH);
	    this.weekday2=cal2.get(Calendar.DAY_OF_WEEK);
	    this.maxDay3 = this.cal3.getActualMaximum(Calendar.DAY_OF_MONTH);
	    this.weekday3=cal3.get(Calendar.DAY_OF_WEEK);
	}
	public mycal() {				//when class is made, 
		this.cal1=Calendar.getInstance();	//class's cals get Instance about calendar
		this.cal2=Calendar.getInstance();
		this.cal3=Calendar.getInstance();
	}
	public void printweek(int maxDay, int weekday,int i,int k) {//print week of month
		if(i>maxDay) {											//about last week of month
    		for(int j=0;j<=6;j++) {								//make blanks to set format
				System.out.print("   ");						
    		}
		}
		for(;i<=maxDay;i++) {									//days of month(normal)
	    	if(i==1) {											//before first day of month
	    		for(int j=1; j<weekday;j++) {					//make blanks to set format
	    			System.out.print("   ");
	    		}
	    	}
	    	System.out.printf("%3d",i);							//print day of month
	    	if(i==maxDay) {										//about week that contains last day
	    		if(weekday%7!=0) {								//except case about last day = Saturday
	    			for(int j=0; j<=(6-(weekday%7));j++) {		//make blank to set format
		    			System.out.print("   ");
		    		}
	    		}
	    	}
	    	if(weekday%7==0) {									//end of week
	    		weekday++;										//move to next day about day of week
	    		i++;											//move to next day
	    		break;
	    	}
	    	weekday++;											//move to next day about day of week
	    }
		if(k==1) {												//about calendar1
			this.i1=i;											//save contents that changed
			this.weekday1=weekday;
		}
		else if(k==2) {												//about calendar2
			this.i2=i;											//save contents that changed
			this.weekday2=weekday;
		}
		else if(k==3) {												//about calendar3
			this.i3=i;											//save contents that changed
			this.weekday3=weekday;
		}
	}
	public void printcal(int year) {							//function to print 3months at once
		for(int k=1;k<=10;k+=3) {								//number of loops is 4	
			this.setcal(year,k);								//set calendar's year and month
	    	for(int i=0;i<6;i++) {								//print calendar by 3 months
	    		printweek(maxDay1,weekday1,i1,1);				//print about 1,4,7,10 month
	    		System.out.print(" ");
	    		printweek(maxDay2,weekday2,i2,2);				//print about 2,5,8,11 month
	    		System.out.print(" ");
	    		printweek(maxDay3,weekday3,i3,3);				//print about 3,6,9,12 month
	    		System.out.println(" ");						//change line
	    	}
    		System.out.println(" ");						//change line
		}
	}
}
public class assign3 {											
	public static void main(String[] args) {					//main function to make result
		Scanner scanner = new Scanner(System.in);				//scanner to take input
		System.out.println("년도를 입력하세요 :");					//call user to take input
		int input = scanner.nextInt();							//take input
		System.out.println();									//change line to set format
		System.out.println();
		mycal newone= new mycal();							//make new object that have class mycal
		newone.printcal(input);									//print calendar
	}
}


package lab0325;

import java.util.Scanner;

public class InsertionSort {
/*
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner sc = new Scanner(System.in);

		int c = sc.nextInt();
		int item[] = new int[c];

		for(int i =0; i < c; i++)
			item[i] = sc.nextInt();

		Sort s = new Sort(item);		

		s.insertion();

		System.out.println();

		for(int i =0; i< item.length;i ++)
			System.out.print(item[i]+" ");



	}
*/
}

class Sort{



	void insertion(int item[], int size){

		int temp,j;
		for( int i =1 ; i < item.length ; i ++){

			temp = item[i];
			j = i;
			while( (j>0)&& (item[j-1]>temp)){
				item[j] = item[j-1];
				j--;
				
			}
			item[j] = temp;
			
		}
		//System.out.println(min+" "+ cnt);
		//System.out.println(item[3]);
		//
		//		swap(item[min],item[cnt]);
		//
		//		cnt++;

		for(int i =0; i< item.length;i ++)
			System.out.print(item[i]+" ");

		System.out.println();

	}


}


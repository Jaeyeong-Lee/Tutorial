package lab0325;

import java.util.Scanner;

public class Test {
	static int C;
	static int n;

	static int board[][];
	static int cache[][];

/*
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Scanner sc = new Scanner(System.in);

		//test case
		C = sc.nextInt();
		//size of n

		for(int k =0; k< C; k++){
			n = sc.nextInt();

			board = new int[n][n];
			cache = new int[n][n];


			for(int i =0; i<n; i++){

				for(int j =0; j <n ; j++){

					board[i][j] = sc.nextInt();
				}
				sc.nextLine();

			}



			if(jump2(0,0) == 1)
				System.out.println("YES");
			else
				System.out.println("NO");
		}

		//YES or NO

	}
*/
	//return 0 NO, return 1 YES
	static int jump2(int y, int x){

		if(y >= n || x >= n) return 0;

		if(y == n-1 && x == n-1) return 1;

		int ret = cache[y][x];

		if(ret != -1) return ret;

		int jumpSize = board[y][x];

		// in java Á¤¼ö³¢¸® ||¾ÈµÇ³ªºÁ.


		return ret = jump2(y+jumpSize,x) + jump2(y, x+jumpSize);
	}

}

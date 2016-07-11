package lab0325;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class P111 {


/*
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		BufferedReader in;
		FileWriter out;

		int testNum;
		int num;
		String arr[][];
		String pt_queen[] = new String[3];

		int size[] = new int[3];
		int ptx,pty;

		int i,j,k;
		String path = P111.class.getResource("").getPath();
		try {

			in = new BufferedReader(new FileReader(path+"input_P111.txt"));
			out = new FileWriter("output.txt");

			testNum = Integer.valueOf(in.readLine());

			for( k = 0; k < testNum; k++ ){

				num = Integer.valueOf(in.readLine());

				arr = new String[num][num];

				String temp = in.readLine();

				// pt_queen[0], pt_queen[1], pt_queen[2]
				pt_queen = temp.split(",");

				// 11, 7, 7  (size+1)/2
				for(i =0; i<3; i++)
					size[i] = pt_queen[i].length();


				for(i =0; i<num; i++)
					for(j=0;j<num;j++)
						arr[i][j] = "0";

				//				System.out.println(pt_queen[0].charAt(0));
				//				System.out.println((int)(pt_queen[0].charAt(0)));

				for(i=0;i<3;i++){
					for(j = 0; j < size[i]+1;j+=4){

						// A queen
						if( i == 0 ){
							ptx = (int)(pt_queen[i].charAt(j))-48;
							pty = (int)(pt_queen[i].charAt(j+2))-48;

							arr[ptx][pty] = "A";
						}else if( i == 1){
							ptx = (int)(pt_queen[i].charAt(j))-48;
							pty = (int)(pt_queen[i].charAt(j+2))-48;

							arr[ptx][pty] = "B";
						}else if( i ==2){
							ptx = (int)(pt_queen[i].charAt(j))-48;
							pty = (int)(pt_queen[i].charAt(j+2))-48;

							arr[ptx][pty] = "C";
						}
					}

				}
				for(i =0; i<num; i++){
					for(j=0;j<num;j++)
						System.out.print(arr[i][j]+ " ");
					System.out.println();
				}System.out.println();

				Queen que = new Queen();

				int reminder = que.matrix(arr, num);

				System.out.println("남아있는 블록 : "+reminder);

				out.write("#"+(k+1)+" "+reminder+"\r\n");
			}



			in.close();
			out.close();



		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


	}

*/


}

class Queen{
	boolean get(int i, int j, String[][] arr, int num){
		if( i < 0 || j <0 || i >= num || j >= num)
			return false;
		return true;
	}

	int matrix (String[][] arr, int num){
		int i,j;
		int reminder=0;

		for( i = 0; i <num ;i ++){
			for(j=0; j<num; j++){

				switch(arr[i][j]){

				case "C":
					int a = 3;
					if( get(i-a,j-a,arr,num) && arr[i-a][j-a] =="0")
						arr[i-a][j-a] = "1";
					if( get(i-a,j,arr,num) && arr[i-a][j] =="0")
						arr[i-a][j] = "1";
					if( get(i-a,j+a,arr,num) && arr[i-a][j+a] =="0")
						arr[i-a][j+a] = "1";
					if( get(i+a,j-a,arr,num) && arr[i+a][j-a] =="0")
						arr[i+a][j-a] = "1";
					if( get(i+a,j,arr,num) && arr[i+a][j] =="0")
						arr[i+a][j] = "1";
					if( get(i+a,j+a,arr,num) && arr[i+a][j+a] =="0")
						arr[i+a][j+a] = "1";
					if( get(i,j-a,arr,num) && arr[i][j-a] =="0")
						arr[i][j-a] = "1";
					if( get(i,j+a,arr,num) && arr[i][j+a] =="0")
						arr[i][j+a] = "1";
				case "B":
					a = 2;
					if( get(i-a,j-a,arr,num) && arr[i-a][j-a] =="0")
						arr[i-a][j-a] = "1";
					if( get(i-a,j,arr,num) && arr[i-a][j] =="0")
						arr[i-a][j] = "1";
					if( get(i-a,j+a,arr,num) && arr[i-a][j+a] =="0")
						arr[i-a][j+a] = "1";
					if( get(i+a,j-a,arr,num) && arr[i+a][j-a] =="0")
						arr[i+a][j-a] = "1";
					if( get(i+a,j,arr,num) && arr[i+a][j] =="0")
						arr[i+a][j] = "1";
					if( get(i+a,j+a,arr,num) && arr[i+a][j+a] =="0")
						arr[i+a][j+a] = "1";
					if( get(i,j-a,arr,num) && arr[i][j-a] =="0")
						arr[i][j-a] = "1";
					if( get(i,j+a,arr,num) && arr[i][j+a] =="0")
						arr[i][j+a] = "1";
				case "A":
					a = 1;
					if( get(i-a,j-a,arr,num) && arr[i-a][j-a] =="0")
						arr[i-a][j-a] = "1";
					if( get(i-a,j,arr,num) && arr[i-a][j] =="0")
						arr[i-a][j] = "1";
					if( get(i-a,j+a,arr,num) && arr[i-a][j+a] =="0")
						arr[i-a][j+a] = "1";
					if( get(i+a,j-a,arr,num) && arr[i+a][j-a] =="0")
						arr[i+a][j-a] = "1";
					if( get(i+a,j,arr,num) && arr[i+a][j] =="0")
						arr[i+a][j] = "1";
					if( get(i+a,j+a,arr,num) && arr[i+a][j+a] =="0")
						arr[i+a][j+a] = "1";
					if( get(i,j-a,arr,num) && arr[i][j-a] =="0")
						arr[i][j-a] = "1";
					if( get(i,j+a,arr,num) && arr[i][j+a] =="0")
						arr[i][j+a] = "1";

				}
			}
		}

		for(i =0 ; i <num; i++){
			for(j =0;j<num;j++){
				if(arr[i][j]=="0")
					reminder++;
				System.out.print(arr[i][j]+ " ");
			}System.out.println();

		}
		return reminder;
	}
}


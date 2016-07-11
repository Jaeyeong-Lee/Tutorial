package lab0325;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class P92 {
/*
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		BufferedReader in;
		FileWriter out;

		String str;	// 파일 입출력
		int testNum; // 테스트케이스

		// 폭탄이 들어갈 2차원 배열?
		String arrNum[][] = new String[3][10];
		String cutStr[] = new String[3]; // 파일 입출력?
		String cutChar[][] = new String[30][30]; // 파일 입출력?

		int num; //배열 크기
		int size[] = new int[3]; // A,B,C형 폭탄 수
		int pt[][] = new int[3][50]; // A,B,C형 폭탄
		int ptx = 0, pty = 0; 	// 좌표변수..
		int i = 0, j, k;
		int remainder;
		try{
			
			String path = P92.class.getResource("").getPath();

			in = new BufferedReader(new FileReader(path+"input.txt"));
			out = new FileWriter("output.txt");
			testNum = Integer.valueOf(in.readLine());

			for(k = 0; k < testNum; k++){
				Bomb bomb = new Bomb();

				num = Integer.valueOf(in.readLine());
				//System.out.println("num : "+num); 7
				
				// string 채로 받음..
				str = in.readLine();
				
				// 다시 정의.. 배열 크기 할당
				arrNum = new String[num][num];
				int startIndex = 0;

				for(i =0; i<3; i++){ // 배열 크기 할당
					int fIndex = str.indexOf(",",startIndex);

					if(fIndex == -1)
						fIndex = str.length();
					cutStr[i] = str.substring(startIndex,fIndex);
					
					System.out.println("cutStr["+i+"] : "+ cutStr[i]);
					startIndex = fIndex +1;
				}

				// size????A,B,C형 폭탄 수... 폭탄 수가 안될 것 같은데..???
				// 그래 폭탄 수 아니야. 그냥 문자열 전체 수
				for(i =0; i<3; i++){
					size[i] = cutStr[i].length();
					System.out.println("size[i] : "+size[i]);
				}
				
				for(i = 0; i<3;i++){
					//split 횟수만큼 배열에 나누어 저장되나??
					//어 그러네, 2차원배열이 되어서 각각 저장하게되네!
					cutChar[i] = cutStr[i].split(" ");
					
				}
				// 아마도.. 8
				for(String ch : cutChar[0])
					System.out.print(ch+" ");
				
					
				System.out.println(cutChar[0].length);
					

				// (size[i] -1) /2 전체에서 -1 왜 뺀거지?? 그 값이 진짜 폭탄 수 같은데...
				for(i = 0; i<3; i++){
					for( j = 0; j <= (size[i] -1)/2 ; j++){
						pt[i][j] = Integer.valueOf(cutChar[i][j]);
					}
				}
				// 0으로 맵 초기화
				for(i = 0; i <num; i++){
					for(j = 0; j < num; j++){
						arrNum[i][j] = "0";
					}
				}
				
				// "\n" 개행되는거 맞아???
				System.out.print("#" + (k+1)+"\n"+ "지도의 크기 : "+ num + "\n");
				System.out.print("폭탄이 떨어진 위치\n");

				for(i = 0; i< 3; i++){
					// ascii 65? A
					System.out.printf("%c형 폭탄 : \n", 65+ i);
					for( j =0; j <= size[i] /2; j++)
						System.out.print(pt[i][j]+" ");
					System.out.println();

				}

				for(i =0; i<3; i++){
					for(j = 0; j <= size[i]/2; j++){

						if( i ==0 ){ //A형 폭탄

							if((i+j)%2 ==0) // x좌표 y좌표 값의 합이 짝수면..? ptx에 ...? 00 02 04 06 x좌표들~~ 
								ptx = pt[i][j];
							else {
								pty = pt[i][j];
								arrNum[ptx][pty] = "A";
							}
						} else if( i == 1){ //B형 폭탄

							if((i+j)%2 ==0){
								pty = pt[i][j];
								arrNum[ptx][pty] = "B";
							}
							else 
								ptx =  pt[i][j];
						}
						else { // C형 폭탄
							if((i+j)%2 == 0)
								ptx = pt[i][j];
							else {
								pty = pt[i][j];
								arrNum[ptx][pty] = "C";
							}

						}

					}
				}

				for(i = 0; i <num; i++){
					for( j=0; j<num;j++)
						System.out.print(arrNum[i][j] + " ");
					System.out.println();
				}
				remainder = bomb.matrix(arrNum,num); // 함수 호출 후 남은 지역 수 반환..
				out.write("#"+(k+1)+ " "+remainder +"\r\n");
				System.out.print("커버안된 지역 : "+remainder + "\n\n");

			}
			in.close();
			out.close();
			
		}catch(NumberFormatException e){
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
*/

}

class Bomb{
	boolean get(int i, int j, String arrNum[][], int num){
		if( i<0 || j <0 || i>= num || j >= num)
			return false;
		return true;
	}

	int matrix(String arrNum[][],int num){
		int i,j;
		int remainder = 0;

		for(i=0; i< num; i++){
			for(j =0; j<num; j++){
				switch( arrNum[i][j]){

				// "C"에서 두칸 떨어진 부분만 1로 바꾸는 것 아닌가??? 
				// 그렇다면 "B", "A"도 함께적용되야할텐데. 아 case문에 break가 업긴 하네?
				case "C":
					if(get(i-3,j,arrNum,num) && arrNum[i-3][j] == "0")
						arrNum[i-3][j] = "1";
					if(get(i,j-3,arrNum,num) && arrNum[i][j-3] == "0")
						arrNum[i][j-3] = "1";
					if(get(i+3,j,arrNum,num) && arrNum[i+3][j] == "0")
						arrNum[i+3][j] = "1";
					if(get(i,j+3,arrNum,num) && arrNum[i][j+3] == "0")
						arrNum[i][j+3] = "1";
				case "B":
					if(get(i-2,j,arrNum,num) && arrNum[i-2][j] == "0")
						arrNum[i-2][j] = "1";
					if(get(i,j-2,arrNum,num) && arrNum[i][j-2] == "0")
						arrNum[i][j-2] = "1";
					if(get(i+2,j,arrNum,num) && arrNum[i+2][j] == "0")
						arrNum[i+2][j] = "1";
					if(get(i,j+2,arrNum,num) && arrNum[i][j+2] == "0")
						arrNum[i][j+2] = "1";
				case "A":
					if(get(i-1,j,arrNum,num) && arrNum[i-1][j] == "0")
						arrNum[i-1][j] = "1";
					if(get(i,j-1,arrNum,num) && arrNum[i][j-1] == "0")
						arrNum[i][j-1] = "1";
					if(get(i+1,j,arrNum,num) && arrNum[i+1][j] == "0")
						arrNum[i+1][j] = "1";
					if(get(i,j+1,arrNum,num) && arrNum[i][j+1] == "0")
						arrNum[i][j+1] = "1";
				}
			}
		}


		System.out.println();

		for(i =0; i<num; i++){
			for(j =0; j< num; j++){

				System.out.print(arrNum[i][j]+" ");

				if(arrNum[i][j] == "0"){
					remainder ++;
				}

			}
			System.out.println();
		}
		return remainder;
	}
}
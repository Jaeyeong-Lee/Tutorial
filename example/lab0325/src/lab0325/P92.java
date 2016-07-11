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

		String str;	// ���� �����
		int testNum; // �׽�Ʈ���̽�

		// ��ź�� �� 2���� �迭?
		String arrNum[][] = new String[3][10];
		String cutStr[] = new String[3]; // ���� �����?
		String cutChar[][] = new String[30][30]; // ���� �����?

		int num; //�迭 ũ��
		int size[] = new int[3]; // A,B,C�� ��ź ��
		int pt[][] = new int[3][50]; // A,B,C�� ��ź
		int ptx = 0, pty = 0; 	// ��ǥ����..
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
				
				// string ä�� ����..
				str = in.readLine();
				
				// �ٽ� ����.. �迭 ũ�� �Ҵ�
				arrNum = new String[num][num];
				int startIndex = 0;

				for(i =0; i<3; i++){ // �迭 ũ�� �Ҵ�
					int fIndex = str.indexOf(",",startIndex);

					if(fIndex == -1)
						fIndex = str.length();
					cutStr[i] = str.substring(startIndex,fIndex);
					
					System.out.println("cutStr["+i+"] : "+ cutStr[i]);
					startIndex = fIndex +1;
				}

				// size????A,B,C�� ��ź ��... ��ź ���� �ȵ� �� ������..???
				// �׷� ��ź �� �ƴϾ�. �׳� ���ڿ� ��ü ��
				for(i =0; i<3; i++){
					size[i] = cutStr[i].length();
					System.out.println("size[i] : "+size[i]);
				}
				
				for(i = 0; i<3;i++){
					//split Ƚ����ŭ �迭�� ������ ����ǳ�??
					//�� �׷���, 2�����迭�� �Ǿ ���� �����ϰԵǳ�!
					cutChar[i] = cutStr[i].split(" ");
					
				}
				// �Ƹ���.. 8
				for(String ch : cutChar[0])
					System.out.print(ch+" ");
				
					
				System.out.println(cutChar[0].length);
					

				// (size[i] -1) /2 ��ü���� -1 �� ������?? �� ���� ��¥ ��ź �� ������...
				for(i = 0; i<3; i++){
					for( j = 0; j <= (size[i] -1)/2 ; j++){
						pt[i][j] = Integer.valueOf(cutChar[i][j]);
					}
				}
				// 0���� �� �ʱ�ȭ
				for(i = 0; i <num; i++){
					for(j = 0; j < num; j++){
						arrNum[i][j] = "0";
					}
				}
				
				// "\n" ����Ǵ°� �¾�???
				System.out.print("#" + (k+1)+"\n"+ "������ ũ�� : "+ num + "\n");
				System.out.print("��ź�� ������ ��ġ\n");

				for(i = 0; i< 3; i++){
					// ascii 65? A
					System.out.printf("%c�� ��ź : \n", 65+ i);
					for( j =0; j <= size[i] /2; j++)
						System.out.print(pt[i][j]+" ");
					System.out.println();

				}

				for(i =0; i<3; i++){
					for(j = 0; j <= size[i]/2; j++){

						if( i ==0 ){ //A�� ��ź

							if((i+j)%2 ==0) // x��ǥ y��ǥ ���� ���� ¦����..? ptx�� ...? 00 02 04 06 x��ǥ��~~ 
								ptx = pt[i][j];
							else {
								pty = pt[i][j];
								arrNum[ptx][pty] = "A";
							}
						} else if( i == 1){ //B�� ��ź

							if((i+j)%2 ==0){
								pty = pt[i][j];
								arrNum[ptx][pty] = "B";
							}
							else 
								ptx =  pt[i][j];
						}
						else { // C�� ��ź
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
				remainder = bomb.matrix(arrNum,num); // �Լ� ȣ�� �� ���� ���� �� ��ȯ..
				out.write("#"+(k+1)+ " "+remainder +"\r\n");
				System.out.print("Ŀ���ȵ� ���� : "+remainder + "\n\n");

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

				// "C"���� ��ĭ ������ �κи� 1�� �ٲٴ� �� �ƴѰ�??? 
				// �׷��ٸ� "B", "A"�� �Բ�����Ǿ����ٵ�. �� case���� break�� ���� �ϳ�?
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
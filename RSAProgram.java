import java.io.*;
import java.util.*;
import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.math.BigInteger;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.security.SecureRandom;

//************************ 
// Garrett and Aaron 
// RSA encryption, decryption and key generation 
// Last modified May 2, 2014, 10:21 am 
// Notes: creates public key and private key together.
//			
//************************ 

public class RSAProgram {
	static int Loaded_key = 0;
	static String Loaded_key_name = ""; 

	static BigInteger Loaded_n = BigInteger.valueOf(0);
	static BigInteger Loaded_d = BigInteger.valueOf(0);
	static BigInteger Loaded_p = BigInteger.valueOf(0);
	static BigInteger Loaded_q = BigInteger.valueOf(0);
	static BigInteger Loaded_e = BigInteger.valueOf(0);
	static BigInteger m = BigInteger.valueOf(0);
	static int Private_key_loaded = 0;
	static int Public_key_loaded = 0;
	
	public static void main(String[] args) throws FileNotFoundException{
		Prompt();
		return;
	}
	public static void Prompt(){
		System.out.println("Agent, please choose one of the options listed: ");
		System.out.println("1 Create a private and public key. ");
		System.out.println("2 Load a key (public or private).");
		System.out.println("3 Encrypt/Decrypt a text file with currently loaded key.");
		System.out.println("4 End simulation.");
		Scanner cin=new Scanner(System.in);
		int command  = cin.nextInt();
		if ( command == 4){
			return;
		}
		Options(command);
	}
	public static void Options(int command){
		if(command == 1){ // create private key
			Private_key();
		}else if(command == 2){ // create public key
			Load_key();
		}else if(command == 3){ // Encrypt/Decrypt
			if(Loaded_key == 1 && Public_key_loaded == 1){
				System.out.println("Please choose: ");
				System.out.println("1 Encrypt");
				System.out.println("2 Decrypt");

				Scanner cin=new Scanner(System.in);
				int choice = cin.nextInt();
				if( choice == 1){
					Encrypt();
				}else if( choice == 2){
					Decrypt();
				}else{
					System.out.println("Agent, you only had two options, let us start over. ");
					Prompt();
				}
			}else if(Loaded_key == 1 && Private_key_loaded == 1){
				System.out.println("Please choose: ");
				System.out.println("1 Encrypt");
				System.out.println("2 Decrypt");

				Scanner cin=new Scanner(System.in);
				int choice = cin.nextInt();
				if( choice == 1){
					Encrypt();
				}else if( choice == 2){
					Decrypt();
				}else{
					System.out.println("Agent, you only had two options, let us start over. ");
					Prompt();
				}
			}
			else{
				System.out.println("Please load a key first. ");
				Load_key();
			}
		}else{
			System.out.println("Agent, that is an invalid command. ");
			Prompt();
		}
	}
	public static void Private_key()  {
	// gets p and q
	// from p and q, we calculate the private key m and then calculate n, e, d

		Scanner cin=new Scanner(System.in);
		BigInteger prime1 = BigInteger.valueOf(0);
		BigInteger prime2 = BigInteger.valueOf(0);
		BigInteger private_key = BigInteger.valueOf(0);
		BigInteger gcd[] = new BigInteger[3];
		
		int bitLength = 640;
		System.out.println("Agent, enter the Bit Length (recommend something like 640):");
		bitLength  = cin.nextInt();
		
		SecureRandom rnd = new SecureRandom();
		int certainty = 90; // 1 - 1/2(90) certainty
		prime1 = new BigInteger(bitLength, certainty, rnd);
		prime2 = new BigInteger(bitLength, certainty, rnd);
		
		private_key = prime1.multiply(prime2);
		m = private_key;
		Loaded_n = ((prime1.subtract(BigInteger.valueOf(1)))).multiply((prime2.subtract(BigInteger.valueOf(1))));
		calc_e(640);
		gcd = inverse(Loaded_n, Loaded_e);
		gcd[2] = gcd[2].mod(Loaded_n);
		if(gcd[2].compareTo(BigInteger.valueOf(0)) == -1){
			gcd[2]=gcd[2].add(Loaded_n);
		}
		Loaded_d=gcd[2];
		// Save to a file
		try{
			PrintWriter writer = new PrintWriter("mykey.privk");
			writer.println("n "+Loaded_n);
			writer.println("d "+Loaded_d);
			writer.println("p "+prime1);
			writer.println("q "+prime2);
			writer.println("e "+Loaded_e);
			writer.close();
		}catch (FileNotFoundException ex){
		}
		Public_key();
	}
	public static void Public_key(){
		try{
			PrintWriter writer = new PrintWriter("mykey.pubk");
			writer.println("n "+Loaded_n);
			writer.println("e "+Loaded_e);
			writer.close();
		}catch (FileNotFoundException ex){
		}
		Prompt();
	}
	
	public static void Load_key(){
		Scanner cin=new Scanner(System.in);
		System.out.println("Which would you like to load: ");
		System.out.println("1 Private key");
		System.out.println("2 Public key");
		int choice = cin.nextInt();
		if( choice == 1){
			Loaded_key_name = "mykey.privk";
			File file = new File(Loaded_key_name);
			try {
				Scanner sc = new Scanner(file);
				int count = 0;
				while (count<5) {
						char l=sc.next().charAt(0);
						BigInteger i = sc.nextBigInteger();
						String Blah = sc.nextLine();
						if(count==0){
							Loaded_n = i;
						}else if(count==1){
							Loaded_d = i;
						}else if(count==2){
							Loaded_p = i;
						}else if(count==3){
							Loaded_q = i;
						}else if(count ==4){
							Loaded_e = i;
						}
						count++;
				}
				m = Loaded_p.multiply(Loaded_q);
				System.out.println("The file has been loaded, Sir.");
				Loaded_key = 1;
				sc.close();
				Private_key_loaded = 1;
				Public_key_loaded = 0;
			} catch (FileNotFoundException ex) {
			}
		// To create a public key from a private key, a private key must be loaded first.
		}else if(choice == 2 && Private_key_loaded == 1){ 
			Loaded_key_name = "mykey.pubk";
			File file = new File(Loaded_key_name);
			try {
				Scanner sc = new Scanner(file);
				int count = 0;
				while (count<2) {
						char l=sc.next().charAt(0);
						BigInteger i = sc.nextBigInteger();
						String Blah = sc.nextLine();
						if(count==0){
							Loaded_n = i;
						}else if(count==1){
							Loaded_e = i;
						}
						count++;
				}
				Loaded_key = 1;
				sc.close();
				Private_key_loaded = 0;
				Public_key_loaded = 1;
			} catch (FileNotFoundException ex) {
			}
		}else if(choice == 2 && Private_key_loaded == 0){
			System.out.println("Agent, you have to load a private key before you can create a public key.");
			Load_key();
		}else{
			System.out.println("Let us try that again, agent.");
			Load_key();
		}
	    
		Prompt();
	}
	public static void Encrypt(){
		
		//variables
		String message = "";
		String compressed_message = "";
		BigInteger encrypted = BigInteger.valueOf(0);
		
		//load file
		Scanner cin=new Scanner(System.in);
		System.out.println("Loading 'encrypt.txt' ... ");
		
		Loaded_key_name = "encrypt.txt";
		File file = new File(Loaded_key_name);
		try {
			Scanner sc = new Scanner(file);
			while (sc.hasNext()) {
				message+=sc.nextLine();
			}
			System.out.println("The file has been loaded, Agent.");
			sc.close();
		} catch (FileNotFoundException ex) {
		}
		
		for(int i = 0; i<message.length(); i++){
			if((message.charAt(i)>=65 && message.charAt(i)<=90) || (message.charAt(i)>=97 && message.charAt(i)<=122) || (message.charAt(i)>=48 && message.charAt(i)<=57)){
				compressed_message += message.charAt(i);
			}
		}
		
		int m_length = ((m.toString(36)).length())-1;
		BigInteger string_size = BigInteger.valueOf(0);
		BigInteger block_size = BigInteger.valueOf(((m.toString(36)).length())-1);
		if(BigInteger.valueOf(compressed_message.length()).compareTo(block_size) == -1 || BigInteger.valueOf(compressed_message.length()).compareTo(block_size) == 0){
			//encrypt whole message
			string_size = new BigInteger(compressed_message, 36);
			encrypted = string_size.modPow(Loaded_e, m);
		
			//write it out to a file
			try{
				PrintWriter writer = new PrintWriter("encryptedmessage.txt");
				writer.println(encrypted.toString(36));
				writer.close();
			}catch (FileNotFoundException ex){
			}
		}else if(BigInteger.valueOf(compressed_message.length()).compareTo(block_size) == 1){
			try{
				PrintWriter writer = new PrintWriter("encryptedmessage.txt");
				for(int i = 0; i<compressed_message.length(); i+=(m_length+1)){
					//encrypt substrings message
					string_size = new BigInteger(compressed_message.substring(i, i+m_length), 36);
					encrypted = string_size.modPow(Loaded_e, m);
			
					//write it out to a file
				
					writer.println(encrypted.toString(36));
					writer.println("\n");
				
				}
				writer.close();
			}catch (FileNotFoundException ex){
			}
		}
		
		Prompt();
	}
	public static void Decrypt(){
		
		String decrypt = "";
		BigInteger decrypt_num = BigInteger.valueOf(0);
		BigInteger decrypt_message = BigInteger.valueOf(0);
	
		Loaded_key_name = "encryptedmessage.txt";
		File file = new File(Loaded_key_name);
		try {
			Scanner sc = new Scanner(file);
			decrypt = sc.nextLine();
			
			decrypt_num = new BigInteger(decrypt, 36);
			
			System.out.println("The encrypted file has been loaded, Agent.");
			sc.close();
		} catch (FileNotFoundException ex) {
		}	
		// Test to try to get d 
		Loaded_d = Loaded_e.modPow(BigInteger.valueOf(-1), Loaded_n);
		decrypt_message = decrypt_num.modPow(Loaded_d, m);

		System.out.println("The message has been decrypted, Agent.");
		try{
			PrintWriter writer = new PrintWriter("decryptedmessage.txt");
				
				writer.println(decrypt_message.toString(36));
				writer.println("\n");
				writer.close();
			}catch (FileNotFoundException ex){
			}
	
	
		Prompt();
	}
	public static BigInteger[] inverse(BigInteger n, BigInteger e){
		//find inverse of e mod n
		BigInteger gcd[] = new BigInteger[3];
	
		if(e == BigInteger.valueOf(0)){
			gcd[0] = n;
			gcd[1] = BigInteger.valueOf(1);
			gcd[2] = BigInteger.valueOf(0);
		}else{
			Loaded_d = n.divide(e);
			gcd = inverse(e, n.remainder(e));
			BigInteger temp = gcd[1].subtract((gcd[2].multiply(Loaded_d)));
			gcd[1] = gcd[2];
			gcd[2] = temp;
		}
		
		return gcd;
	}
	
	
	public static void calc_e(int bitLength){
		SecureRandom rnd = new SecureRandom();
		int certainty = 90;
		Loaded_e = BigInteger.probablePrime(bitLength, rnd);
		if(inverse(Loaded_n, Loaded_e)[0].compareTo(BigInteger.valueOf(1)) == 0){
			return;
		}else{
			calc_e(bitLength);
		}
	}
	
}
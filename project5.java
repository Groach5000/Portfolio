import java.io.*;
import java.util.*;
import java.nio.channels.*;
import java.io.RandomAccessFile;
import java.io.IOException;
import java.util.Scanner;
import java.io.File;

// Garrett Roach
// Last Modified December 17, 2013 4:44
// Random Access File
// Operating Systems final project

// Note:  Will give error if you use fake information
//   such as: Code: ggg, City: g, State: g, Airport: g, Country: g
//   what it will do is count the record as a size 75 instead of 77 
//   this is because state and country have to be of size 2.


public class project5 {

private static final int RECORD = 77;

    public static void main(String[] args) 
    {
		System.out.println("Please Type:");
		System.out.println("Add | List | Search | Defrag | Remove | Exit");
		System.out.println();
		String Command;
		do{
			Scanner sc = new Scanner(System.in);
			Command = sc.next();		
			
			if(Command.equals("add") || Command.equals("Add")){
				RandomAccessFile file = null;
			
				String Code, Airport, City;
				String State, Country;
				
				System.out.println("Please Input Code: ");
				Code = sc.next();
				System.out.println("Please Input City: ");
				City = sc.next();
				System.out.println("Please Input Airport: ");
				sc.nextLine();
				Airport = sc.nextLine();
				System.out.println("Please Input State: ");
				State = sc.next();			
				System.out.println("Please Input Country: ");
				Country = sc.next();
				
				try{
					file = new RandomAccessFile("NewRAF.dat","rw");
					long FileSize = file.length();
					file.seek(FileSize);
					file.writeUTF(Code);// size 3
					file.writeUTF(City);
					for(int i = 0; i<30-City.length();i++)
						file.writeByte(30);	
					file.writeUTF(State);// size 2
					file.writeUTF(Country);// size 2
					file.writeUTF(Airport);
					for(int i = 0; i<30-Airport.length();i++)
						file.writeByte(30);
					
					 file.close();
				}catch(Exception e) {
					e.getStackTrace();
				}
			}
			else if(Command.equals("List") || Command.equals("list")){
				
				RandomAccessFile file = null;
			
				String Code = null, Airport = null, City = null;
				String State = null, Country = null;
				
				try{
					file = new RandomAccessFile("NewRAF.dat","rw");
					//System.out.println(file.length());
					long FileSize = file.length();
					file.seek(0);
					long NUMRecords = FileSize/RECORD;
					for(int j = 0; j< NUMRecords; j++){
						Code = file.readUTF();
						City = file.readUTF();
						for(int i = 0; i<30-City.length();i++)
							file.readByte();
						State = file.readUTF();
						Country = file.readUTF();
						Airport = file.readUTF();
						for(int i = 0; i<30-Airport.length();i++)
							file.readByte();
						if(!Code.equals("..."))	
							System.out.println("Code: " +Code+ " City: "+City+ " State: "+State+" Country: "+Country+" Airport: "+Airport);
					}
					file.close();
				}catch(Exception e) {
					e.getStackTrace();
				}
			}
			else if(Command.equals("Defrag") || Command.equals("defrag")){
				RandomAccessFile file = null;
				String Code = null, Airport = null, City = null;
				String State = null, Country = null;
				int defrag = 0;
				try{
					file = new RandomAccessFile("NewRAF.dat","rw");
					long FileSize = file.length();
					file.seek(0);
					long NUMRecords = FileSize/RECORD;
					for(int j = 0; j< NUMRecords; j++){
					
						Code = file.readUTF();
						City = file.readUTF();
						for(int i = 0; i<30-City.length();i++)
							file.readByte();
						State = file.readUTF();
						Country = file.readUTF();
						Airport = file.readUTF();
						for(int i = 0; i<30-Airport.length();i++)
							file.readByte();
						if(Code.equals("...")){	
							// if item has been deleted and thus white space, remove it
							System.out.println("White space found.");
							file.seek(j*RECORD);
							file.setLength(FileSize-77);
							defrag = 1;
						}
						//System.out.println(file.length());
					}
					if(defrag == 1)
						System.out.println("The file has been defraged.");
					else
						System.out.println("No defrag needed.");

					file.close();
				}catch(Exception e) {
					e.getStackTrace();
				}
			}
			else if(Command.equals("remove") || Command.equals("Remove")){
				RandomAccessFile file = null;
				String Code = null, Airport = null, City = null;
				String State = null, Country = null;
				System.out.print("Please enter the code you wish to Remove: ");
				String Look_For_Code = sc.next();
				int found = 0;
				try{			
					file = new RandomAccessFile("NewRAF.dat","rw");
					//System.out.println(file.length());
					long FileSize = file.length();
					file.seek(0);
					long NUMRecords = FileSize/RECORD;
					for(int j = 0; j< NUMRecords; j++){
						Code = file.readUTF();
						City = file.readUTF();
						for(int i = 0; i<30-City.length();i++)
							file.readByte();
						State = file.readUTF();
						Country = file.readUTF();
						Airport = file.readUTF();
						for(int i = 0; i<30-Airport.length();i++)
							file.readByte();
						if(Look_For_Code.equals(Code)){
							found = 1;
							file.seek(j*77);
							file.writeUTF("...");
							System.out.println("Item has been removed.");
						}
					}
					if(found == 0)
						System.out.println("Sorry no item by the name '"+Look_For_Code+"' found.");
					file.close();
				}catch(Exception e) {
					e.getStackTrace();
				}
			}
			else if(Command.equals("Search") || Command.equals("search")){
				RandomAccessFile file = null;
				String Code = null, Airport = null, City = null;
				String State = null, Country = null;
				System.out.print("Please enter the code you wish to search for: ");
				String Look_For_Code = sc.next();
				int found = 0;
				try{
					file = new RandomAccessFile("NewRAF.dat","rw");
					long FileSize = file.length();
					file.seek(0);
					long NUMRecords = FileSize/RECORD;
					for(int j = 0; j< NUMRecords; j++){
						Code = file.readUTF();
						City = file.readUTF();
						for(int i = 0; i<30-City.length();i++)
							file.readByte();
						State = file.readUTF();
						Country = file.readUTF();
						Airport = file.readUTF();
						for(int i = 0; i<30-Airport.length();i++)
							file.readByte();
						if(Look_For_Code.equals(Code)){
							found = 1;
							System.out.println("Item found!");
							System.out.println("Code: " +Code+ " City: "+City+ " State: "+State+" Country: "+Country+" Airport: "+Airport);
						}
					}
					if(found == 0)
						System.out.println("Sorry no item by the name '"+Look_For_Code+"' found.");
					file.close();
				}catch(Exception e) {
					e.getStackTrace();
				}
				
			}
			else if(Command.equals("Exit") || !Command.equals("Exit"))
				break;
			else{
				System.out.println("Please Choose one of the Options:");
				System.out.println("Add | List | Search | Defrag | Remove | Exit");
			}
		}while(!Command.equals("Exit") || !Command.equals("Exit"));
	}

}
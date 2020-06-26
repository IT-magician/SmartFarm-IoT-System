

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.RandomAccessFile;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class Streaming
 */
@WebServlet("*.mp4")
public class Streaming extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Streaming() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
    private String __Dir = "E:\\videos\\";
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		String FileName = request.getServletPath().substring(1);
   		File file = new File(__Dir+FileName);
   		String fileSize = String.valueOf(file.length());
   		String rangeHeader = request.getHeader("range");
   		
   		/*if(!(new File(__Dir, FileName)).exists())
   		{
   			__Dir = System.getProperty("user.dir") + "\\"; // �� PC>������>videos�� �������� �������� ���� ���, Tomcat�� ����Ǵ� ��ο��� ������ ã��
   		
   		}*/
   		
   		//progressbar ���� Ư�� ��ġ�� Ŭ���ϰų� �ؼ� ���� ��ġ�� ������ ��û�� �� �����Ƿ�
           //������ ������ ��ġ���� �о���� ���� RandomAccessFile Ŭ������ ����Ѵ�.
           //�ش� ������ ���� ��� ���� �߻�
   		
           RandomAccessFile randomFile = new RandomAccessFile(new File(__Dir, FileName), "r");

           long rangeStart = 0; //��û ������ ���� ��ġ
           long rangeEnd = 0;  //��û ������ �� ��ġ
           boolean isPart=false; //�κ� ��û�� ��� true, ��ü ��û�� ��� false

           //randomFile �� Ŭ���� �ϱ� ���Ͽ� try~finally ���
           try{
               //������ ���� ũ��
               long movieSize = randomFile.length();
               //��Ʈ�� ��û ����, request�� ������� range�� �д´�.
               String range = request.getHeader("range");
          System.out.println("range: " + range);

               //�������� ���� range ������ �ٸ���, �⺻ ������ "bytes={start}-{end}" �����̴�.
               //range�� null�̰ų�, reqStart��  0�̰� end�� ���� ��� ��ü ��û�̴�.
               //��û ������ ���Ѵ�.
               if(range!=null) {
                   //ó���� ���Ǹ� ���� ��û range�� end ���� ���� ��� �־���
                   if(range.endsWith("-")){
                       range = range+(movieSize - 1);
                   }
                   int idxm = range.trim().indexOf("-");                           //"-" ��ġ
                   rangeStart = Long.parseLong(range.substring(6,idxm));
                   rangeEnd = Long.parseLong(range.substring(idxm+1));
                   if(rangeStart > 0){
                       isPart = true;
                   }
              }else{   //range�� null�� ��� ������ ��ü ũ��� �ʱⰪ�� �־���. 0���� �����ϹǷ� -1
                   rangeStart = 0;
                   rangeEnd = movieSize - 1;
              }

              //���� ���� ũ��
              long partSize = rangeEnd - rangeStart + 1;
         System.out.println("accepted range: " + rangeStart+"-"+rangeEnd+"/"+partSize+" isPart:"+isPart);

              //���۽���
              response.reset();

              //��ü ��û�� ��� 200, �κ� ��û�� ��� 206�� ��ȯ���� �ڵ�� ����
              response.setStatus(isPart ? 206 : 200);

              //mime type ����
              response.setContentType("video/mp4");

              //���� ������ ��忡 �־��ش�. �������� ���� ��ü ũ�⸦ �ִ´�.
              response.setHeader("Content-Range", "bytes "+rangeStart+"-"+rangeEnd+"/"+movieSize);
              response.setHeader("Accept-Ranges", "bytes");
              response.setHeader("Content-Length", ""+partSize);
      
              OutputStream out = response.getOutputStream();
              //������ ������ ���۽��� ��ġ ����
              randomFile.seek(rangeStart);
      
              //���� ����...  java io�� 1ȸ ���� byte���� int�� ������
              //������ ������ ��� int�����δ� ó�� �ȵǴ� ũ���� ������ �����Ƿ�
              //8kb�� �߶� ������ ũ�Ⱑ ũ���� ������ ���� �ʵ��� ����
              int bufferSize = 8*1024;
              byte[] buf = new byte[bufferSize];
              do{
                  int block = partSize > bufferSize ? bufferSize : (int)partSize;
                  int len = randomFile.read(buf, 0, block);
                  out.write(buf, 0, len);
                  partSize -= block;
              }while(partSize > 0);
        System.out.println("sent " + FileName + " " + rangeStart + "-" + rangeEnd);
          }catch(IOException e){
              //���� �߿� �������� �ݰų�, ȭ���� ��ȯ�� ��� �����ؾ� �ϹǷ� �������.
              // progressBar�� Ŭ���� ��쿡�� Ŭ���� ��ġ������ ���û�� �����Ƿ� ���� ���.
         System.out.println("������ ��� �Ǿ���" ); 
          }finally{
              randomFile.close();
          }
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}

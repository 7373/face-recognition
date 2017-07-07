package com;

import java.io.*;
import java.util.List;

public class RegisterAction {
	
	public Template getTemp() {
		return temp;
	}
	public void setTemp(Template temp) {
		this.temp = temp;
	}
	public TemplateDao getTempdao() {
		return tempdao;
	}
	public void setTempdao(TemplateDao tempdao) {
		this.tempdao = tempdao;
	}
	private Template temp;
	private TemplateDao tempdao;
	private List<File> file;
	private List<String> fileFileName;
	public List<File> getFile() {
		return file;
	}
	public void setFile(List<File> file) {
		this.file = file;
	}
	public List<String> getFileFileName() {
		return fileFileName;
	}
	public void setFileFileName(List<String> fileFileName) {
		this.fileFileName = fileFileName;
	}
	public String execute()
	{
		if(tempdao.save(temp))
		{
			String root="D:\\应用\\apache-tomcat-6.0.45\\webapps\\AIVISION\\image";
			
			InputStream is;
			try {
				
			is = new FileInputStream(file.get(0));
			
			String name=temp.getCode()+".jpg";
			
			OutputStream os = new FileOutputStream(new File(root,name));

			byte[] buffer = new byte[500];

			@SuppressWarnings("unused")
			int length = 0;

			while (-1 != (length = is.read(buffer, 0, buffer.length))) {
				os.write(buffer);
			}

			os.close();
			is.close();
			
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			return "success";
		}
		else 
			return "error";
	}

}

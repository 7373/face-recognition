package com;

import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import test.Identify;

public class TemplateDao extends HibernateDaoSupport {

	
	public boolean save(Template tem) { 
		if(tem!=null)
		{
			try
			{
				this.getHibernateTemplate().save(tem);
				return true;
			}
			catch(Exception e)
			{
				e.printStackTrace();
				return false;
			}
		}
		return false;
	}
	
	@SuppressWarnings("unchecked")
	public List<Template> getFeatures()
	{
		try {
			@SuppressWarnings("unchecked")
			List<Template> list= this.getHibernateTemplate().find("FROM Template");
			/*Session session = getSession();
			Query query = session.createQuery("SELECT feature FROM data");
			query.executeUpdate();*/
			return list;
		} catch(Exception e) {
			e.printStackTrace();
			return null;
		}
	}
	
	public float[] convert(String str)
	{
		float[] fo=new float[2048];
		String[] temp=str.split(" ");
		//System.out.println("temp:"+temp.length);
		for(int i=0;i<temp.length;i++)
		{
			fo[i]=Float.parseFloat(temp[i]);
		}
		return fo;
	}
	
	public Template compare(String feature)
	{
		System.load("D:\\应用\\apache-tomcat-6.0.45\\webapps\\AIVISION\\WEB-INF\\classes\\similarity.dll");
		float[] fo=convert(feature);
		List<Template> list=getFeatures();
		float[] sort=new float[2048];
		//System.out.println("listsize:"+list.size());
		for(int i=0;i<list.size();i++)
		{
			sort[i]=new Identify().similarity(fo, convert(list.get(i).getFeature()));
		}
		System.out.println("比对结果:"+list.get(getMax(sort)).getName());
		return list.get(getMax(sort));	
	}
	
	public int getMax(float[] ft)
	{
		int max=0;
		float maxn=ft[0];
		for(int i=1;i<ft.length;i++)
		{
			if(ft[i]>maxn)
			{
				max=i;
				maxn=ft[i];
			}
		}
		return max; 
	}

}

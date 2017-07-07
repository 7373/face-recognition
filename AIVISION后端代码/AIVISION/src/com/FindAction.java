package com;

public class FindAction {
	
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
	public String getFeature() {
		return feature;
	}
	public void setFeature(String feature) {
		this.feature = feature;
	}
	private Template temp;
	private TemplateDao tempdao;
	private String feature;
	
	public String execute()
	{
		Template tmp=tempdao.compare(feature);
		temp=tmp;
		temp.setFeature(null);
		return "success";
	}
	
	

}

package com;

public class Template {
	private String name;
	private String code;
	private String sex;
	private String feature;
	private String type;
	public Template(String name, String code, String sex, 
			String feature, String type) {
		super();
		this.name = name;
		this.code = code;
		this.sex = sex;
		this.feature = feature;
		this.type = type;
	}
	public Template() {
		super();
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getFeature() {
		return feature;
	}
	public void setFeature(String feature) {
		this.feature = feature;
	}
	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	

}

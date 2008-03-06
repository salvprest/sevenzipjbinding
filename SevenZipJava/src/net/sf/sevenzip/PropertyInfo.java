package net.sf.sevenzip;

public class PropertyInfo {
	public String name;
	public int propID;
	public Class<?> varType;
	
	@Override
	public String toString() {
		return "name=" + name + "; propID=" + propID + "; varType=" + varType.getCanonicalName();
	}
}

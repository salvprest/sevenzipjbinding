package net.sf.sevenzipjbinding.junit;

import net.sf.sevenzipjbinding.ArchiveFormat;

public class ExtractSingleFileZipPassCallbackTest extends ExtractSingleFileAbstractPassTest {

	public ExtractSingleFileZipPassCallbackTest() {
		super(ArchiveFormat.ZIP, 0, 5, 9);
		usingPasswordCallback();
	}

}

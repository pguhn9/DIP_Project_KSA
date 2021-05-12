## DIP_Scale



#### DownSampling  이미지 축소

Doc에 작성
```c
void CMFCApplication05111Doc::OnDownSampling()
{
	int i, j;
	CDownSampleDlg2 dlg;

	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		m_Re_width = m_width / dlg.m_DownSampleRate;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];


		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i*m_Re_width + j]
					= m_InputImage[(i*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*j];
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}
```
      

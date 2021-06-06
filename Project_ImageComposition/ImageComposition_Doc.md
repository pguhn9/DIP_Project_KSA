## 이미지 합성 팀프로젝트
##### 날짜: 2021.06.05
-------------------------------


## 1. 프로젝트 목적
* bmp 이미지 파일 입력 , 출력 받기
* 인물, 배경 이미지 합성
* MFC 프로젝트 이용한 윈도우 프로그램으로 구현

## 2. 구조 설계
### 1) 프로젝트 구조 개요


<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/Project_structure_info.PNG" width="550px" height="700px" title="Project_structure_info" alt="Project_structure_info"></img><br/>


### 2) 다이어그램
#### (1) Sequence Diagram

<img src="https://user-images.githubusercontent.com/72690336/120916312-e4986300-c6e3-11eb-9ddf-d606a59ff76d.png" width="650px" height="500px" title="Project_structure_info" alt="Project_structure_info"></img><br/>

### (2) Class Diagram

<img src="https://user-images.githubusercontent.com/72690336/120916224-545a1e00-c6e3-11eb-9d5e-1e18adf9cd1b.png" width="550px" height="300px" title="Project_structure_info" alt="Project_structure_info"></img><br/>




### 3) 주요 클래스 생성
* ImageCompositionDoc 클래스
  - 파일을 읽어들이기 위한 CFile 객체, 비트맵 해더를 저장하기 위한 BITMAPFILEHEADER, BITMAPINFOHEADER 객체, 8비트일 경우 색상 파레트를 저장하기 위한 RGBQUAD 객체를 필드로 갖는다.
  - bmp 이미지 비트 수 확인, 컬러 흑백 확인하는 기능을 포함한다.
  - 이미지 가로 세로 길이와 입력 이미지, 출력 이미지, 마스크 이미지를 저장하기 위한 필드를 갖는다.
  - 출력 이미지를 저장하는 함수를 포함한다.
  - 입력 이미지, 출력 이미지, 마스크 이미지를 합성하는 기능을 포함한다.

* ImageCompositionView 클래스
  - 입력된 이미지를 출력하기 위한 기능 포함.
  - 영상합성 메뉴 버튼 커맨드(ID_IMG_COMP)와 기능을 연결하는 함수 포함.


* CImgComposition 클래스
  - 이미지 합성을 실행하는 클래스.
  - 이미지 합성을 위한 이미지 처리 함수들을 포함하고 있다.

### 4) 주요 기능(함수)
* ImageCompositionDoc 클래스 안의 함수
  - OnOpenDocument 함수 : 입력 이미지를 열어서 bmp헤더 정보와 이미지 값을 변수에 저장하는 함수.
  - OnSaveDocument 함수 : 출력 이미지를 대화상자로 지정한 위치에 bmp 형식으로 저장하는 함수.
  - OnImgComp 함수 : 배경 이미지와 마스크 이미지를 입력 받아 CImgComposition 객체를 통해 합성이미지를 출력이미지에 저장하는 함수.
* ImageCompositionView 클래스 안의 함수
  - OnDraw 함수 : 현재 입력 이미지와 출력 이미지를 프로그램상으로 보여주는 함수.
  - OnImgComp 함수 : 영상합성 메뉴 버튼 커맨드(ID_IMG_COMP)와 기능을 연결하는 함수
* CImgComposition 클래스 안의 함수
  - ImageComposition 함수 : 입력, 배경, 마스크, 출력 이미지를 받아서 이미지 프로세싱 함수들을 이용해 합성 이미지를 반환하는 함수.
  - ImgFrameAnd 함수 : 두 이미지를 AND연산한 결과를 반환하는 함수.
  - ImgNot 함수 : 한 이미지를 반전하는 함수.
  - ImgFrameSum 함수 : 두 이미지를 SUM연산한 결과를 반환하는 함수.
  - ImgBinary 함수 : 한 이미지를 이진화 하는 함수.

### 5) grabcut 마스크 생성 코드
* 프로그램 : python
* 소스코드 : grabcutlena.py
* 사용 알고리즘 : opencv(Grapcut 알고리즘)
: 인물 이미지의 수동으로 이미지 외각선을 검정선으로 이미지 내부를 흰선으로 표시하고 마스킹 소리
</br>
* 레나 라인 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/lena_mask_line.jpg" width="256px" height="256px" title="lena_mask_line" alt="lena_mask_line"></img><br/>
* 레나 그랩컷 첫번째
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/grabcut1.PNG" width="256px" height="256px" title="lena_mask_line" alt="lena_mask_line"></img><br/>
* 레나 그랩컷 두번째
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/grabcut2.PNG" width="256px" height="256px" title="lena_mask_line" alt="lena_mask_line"></img><br/>
* 레나 그랩컷 마스크 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/grabcut2_0255.PNG" width="256px" height="256px" title="lena_mask_line" alt="lena_mask_line"></img><br/>
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/lena_mask_result.bmp" width="256px" height="256px" title="lena_mask_line" alt="lena_mask_line"></img><br/>

* 개선할 점
    * 이미지 오브젝트 중간에 있는 노이즈 제거 필요
    * 수동으로 이미지의 테두리와 오브젝트를 선을 그어야해서 자동으로 마스킹을 딸 수 있는 딥러닝 기법 도전(unet)


### 6) 자동 마스크 생성
* 프로그램 : python
* 소스코드 : lenna.ipynb
* 학습 데이터 : JPEG 사람 데이터 56599장
* 라벨 : Annotations 마스킹 데이터 
* 사용 알고리즘 : U-NET

<img src="https://user-images.githubusercontent.com/72690336/120916413-7dc77980-c6e4-11eb-9b34-e4c3472e866c.png" width="550px" height="500px" title="Project_structure_info" alt="Project_structure_info"></img><br/>

* 결과

훈련셋

<img src="https://user-images.githubusercontent.com/72690336/120917129-5b375f80-c6e8-11eb-8c3a-bbab7c6aecfb.png" width ="450px" height="400px" title="Project_structure_info" alt="Project_structure_info"></img><br/>

레나이미지 마스킹 결과

<img src="https://user-images.githubusercontent.com/72690336/120917178-9d60a100-c6e8-11eb-832c-6bcf0f05c1d3.png" width ="350px" height="250px" title="Project_structure_info" alt="Project_structure_info"></img><br/>

* 개선할 점
    * 히스토그램 평활화, 샤프닝 등 객체를 강조하는 이미지 처리기법 적용
    * 전신 데이터가 많은 훈련셋에 비해 레나 이미지의 경우 상반신만 있는 초상화이므로, ImageGenerator 확대 관련 파라미터 조정 후 성능 재측정


따라서 직접 딴 마스크로 진행
</br>
## 4. 결과 이미지
#### 컬러이미지
* lena 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/lena512color.bmp" width="256px" height="256px" title="lena512color" alt="lena512color"></img><br/>
* 배경 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/background512color.bmp" width="256px" height="256px" title="background512color" alt="background512color"></img><br/>

* 합성 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/lenacolorbackground1.bmp" width="256px" height="256px" title="lena512color_background" alt="lena512color_background"></img><br/>

#### 흑백이미지
* lena 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/lena2.bmp" width="256px" height="256px" title="lena2" alt="lena2"></img><br/>

* 배경 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/nightview2.bmp" width="256px" height="256px" title="nightview2" alt="nightview2"></img><br/>

* 합성 이미지
<br/>
<img src="https://github.com/pguhn9/DIP_Project_KSA/blob/main/Project_ImageComposition/project_image/lenanightview1.bmp" width="256px" height="256px" title="lenanightview1" alt="lenanightview1"></img><br/>

import numpy as np
import cv2
import matplotlib.pyplot as plt


def main():

    # 1. Import pictures
    img_src = cv2.imread("lena_color.jpg")
    img_rgb = cv2.cvtColor(img_src, cv2.COLOR_BGR2RGB)

    # 2. Create a mask picture
    mask = np.zeros(img_src.shape[:2], np.uint8)
    bg_model = np.zeros((1, 65), np.float64)
    fg_model = np.zeros((1, 65), np.float64)

    # 3. Execution area foreground and background segmentation
    rect = (50, 50, 400, 500)
    cv2.grabCut(img_src, mask, rect, bg_model, fg_model, 5, cv2.GC_INIT_WITH_RECT)

    # 4. Import manual mask pictures
    mask2 = cv2.imread("lena_mask_line.jpg", 0)
    mask2_show = cv2.imread("lena_mask_line.jpg", -1)
    m2_rgb = cv2.cvtColor(mask2_show, cv2.COLOR_BGR2RGB) #RGB 뒤집기

    # 5. Perform mask foreground segmentation
    mask[mask2 == 0] = 0 # 마스크2에 있는 검정선 0
    mask[mask2 == 255] = 1 # 마스크2에 있는 하얀선 1
    mask, bg_model, fg_model = cv2.grabCut(img_src, mask, None, bg_model, fg_model, 5, cv2.GC_INIT_WITH_MASK)

    mask = np.where((mask == 2) | (mask == 0), 0, 255).astype("uint8") ## 0과 2값 부분을 0 으로 나머지를 255로

    print(mask[200])


    #save img
    cv2.imwrite("lena_mask_result.bmp", mask)

    # 7. Display results
    plt.figure("show result", figsize=(12, 6))
    plt.subplot(131)
    plt.imshow(m2_rgb)
    plt.axis("off")


    plt.subplot(132)
    plt.imshow(mask)
    plt.axis("off")

    plt.show()


if __name__ == '__main__':
    main()
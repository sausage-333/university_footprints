# EE Co-op Internship at Naver

This folder contains the mid-term & final-term presentation files made at Naver's internship. I was in the Audio Platform department for about 6 months starting from March 2018 to August 2018. I co-worked with Ji-yoon Shin who joined the internship at the same time. **Ji-yoon and I tried to develop 3D Audio library written in Python which makes sound spatially using HRTF.** HRTF is the signal which makes audio spatially if you convolution with the original audio. Presentations are written in English, so please check if you want. Following is my contribution.

-----------------------
### Midterm presentation
1. Interpolating issues of HRTF(Head-related Transfer Function)
- I needed to interpolate the HRTF, since its database is not from continuous directions. Given HRTF was from only several directions, so interpolating was needed in order to refer the arbitrary directions. Bilinear scheme was selected.

2. Getting interpolated HRTF with given arbitrary directions
- Arbitrary azimuth and elevation are given to input, then bilinear interpolated HRTF is given to output. I made grids and indexed each of them to load the 4 nearest HRTFs. These 4 HRTFs will be the ingredients of the bilinear interpolation.

### Final presentation
1. Implementing frame operation by class
- Ji-yoon implemented frame-by-frame operation for the audio input in function, and I converted it to class for more readability and code maintenance.

2. Modeling HRTF to filter coefficients
- Our final goal was to apply in real-time, so faster speed was necessary. Instead of convolutioning audio with HRTFs, I modeled HRTF to several filter coefficients using Prony's method. Filtering with coefficients only takes about 7% in comparison with convolutioning HRTFs. There were 3 main issues to make this functions, modeling HRTF, making filter coefficients table, and referring to that table.

3. Attenuation function added
- Since there is more energy loss in high frequency at far distance, I implemented near-field and far-field attenuation respectively. It makes sound more alive and well.

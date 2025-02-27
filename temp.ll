%struct.A = type { i32, i32, i32 }

@thingie = dso_local global [50 x %struct.A] zeroinitializer, align 4

define dso_local noundef i32 @_Z6squarev() #0 {
  %1 = load i32, ptr getelementptr inbounds (%struct.A, ptr @thingie, i32 0, i32 1), align 4
  %2 = load i32, ptr getelementptr inbounds (%struct.A, ptr getelementptr inbounds ([50 x %struct.A], ptr @thingie, i32 0, i32 2), i32 0, i32 1), align 4
  %3 = mul nsw i32 %1, %2
  %4 = load i32, ptr getelementptr inbounds (%struct.A, ptr getelementptr inbounds ([50 x %struct.A], ptr @thingie, i32 0, i32 20), i32 0, i32 2), align 4
  %5 = mul nsw i32 %3, %4
  ret i32 %5
}

attributes #0 = { mustprogress noinline nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="arm1176jzf-s" "target-features"="+armv6kz,+dsp,+fp64,+strict-align,+vfp2,+vfp2sp,-aes,-d32,-fp-armv8,-fp-armv8d16,-fp-armv8d16sp,-fp-armv8sp,-fp16,-fp16fml,-fullfp16,-neon,-sha2,-thumb-mode,-vfp3,-vfp3d16,-vfp3d16sp,-vfp3sp,-vfp4,-vfp4d16,-vfp4d16sp,-vfp4sp" }
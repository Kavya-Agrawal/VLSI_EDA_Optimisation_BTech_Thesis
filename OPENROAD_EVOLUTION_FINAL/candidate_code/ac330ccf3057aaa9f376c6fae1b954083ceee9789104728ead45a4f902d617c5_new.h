// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.51937741;
  double density_weight = 0.48720358;
  double prefix_weight = 0.44355996;
  double neighborhood_weight = 0.22337422;
  double late_weight = 0.23779514;
  double critical_weight = 0.17199659;
  unsigned budget = 32;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning

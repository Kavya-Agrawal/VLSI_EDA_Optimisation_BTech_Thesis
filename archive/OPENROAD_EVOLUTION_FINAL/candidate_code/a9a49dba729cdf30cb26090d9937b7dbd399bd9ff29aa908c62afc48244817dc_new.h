// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08301680;
  double density_weight = 0.22179356;
  double prefix_weight = 0.31745013;
  double neighborhood_weight = 0.12210206;
  double late_weight = 0.18090150;
  double critical_weight = 0.05966660;
  unsigned budget = 18;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
